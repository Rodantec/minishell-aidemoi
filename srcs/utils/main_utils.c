/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:39:46 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 17:39:46 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_first_command(t_token *tokens)
{
	t_token	*current;
	t_token	*temp;

	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
		{
			temp = tokens;
			while (temp && temp->next != current)
				temp = temp->next;
			if (!temp || !is_redirection(temp))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	handle_redir_only_process(t_token *tokens, t_env *envp)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redirections(tokens, envp, tokens, NULL) == 0)
		g_global.exit_status = 0;
	else
		g_global.exit_status = 1;
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (1);
}

static int	process_pipeline(t_pipeline *pipeline, t_env *envp, t_token *tokens)
{
	int	pipeline_result;

	if (pipeline->cmd_count == 1)
		execute_single_command(tokens, envp,pipeline);
	else
	{
		pipeline_result = execute_pipeline(pipeline, envp, tokens);
		if (pipeline_result != -1)
			g_global.exit_status = pipeline_result;
	}
	return (0);
}

int	process_line(char *line, t_env *envp)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	tokens = lexer(line);
	if (!tokens)
		return (0);
	if (check_syntax_errors(tokens) == -1)
		return (free_tokens(&tokens), 0);
	if (!find_first_command(tokens) && contains_redirection(tokens) > 0)
	{
		handle_redir_only_process(tokens, envp);
		free_tokens(&tokens);
		return (0);
	}
	pipeline = create_pipeline(tokens);
	if (!pipeline)
		return (free_tokens(&tokens), 0);
	process_pipeline(pipeline, envp, tokens);
	free_tokens(&tokens);
	free_pipeline(pipeline);
	return (1);
}

void	init_global(t_env *envp)
{
	g_global.env = envp;
	g_global.shell_status = 0;
	g_global.exit_status = 0;
	g_global.signal_received = 0;
	g_global.child_pid = 0;
}
