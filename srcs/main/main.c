/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/23 12:50:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built_in.h"
#include "../includes/pipeline.h"

t_global	g_global = {0};

char	*prompt_and_read(void)
{
	char	*line;

	g_global.signal_received = 0;
	line = readline("minishell> ");
	if (!line)
	{
		if (g_global.signal_received == SIGINT)
		{
			g_global.signal_received = 0;
			return (ft_strdup(""));
		}
		if (g_global.shell_status == 0)
		{
			printf("exit\n");
			exit(g_global.exit_status);
		}
		return (NULL);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

void	execute_single_command(t_token *tokens, t_env *envp)
{
	int			result;
	t_command	*cmd;
	t_token		*current;
	int			has_command;
	int			saved_stdout;
	int			saved_stdin;
	char		*path; // Nouvelle variable pour vérifier le chemin

	result = 0;
	current = tokens;
	has_command = 0;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
		{
			has_command = 1;
			break ;
		}
		current = current->next;
	}
	if (!has_command)
	{
		if (contains_redirection(tokens) > 0)
		{
			saved_stdout = dup(STDOUT_FILENO);
			saved_stdin = dup(STDIN_FILENO);
			if (handle_redirections(tokens) == 0)
				result = 0;
			else
				result = 1;
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdout);
			close(saved_stdin);
		}
		g_global.exit_status = result;
		return ;
	}
	if (init_command(tokens, &cmd) < 0)
		return ;
	
	// Nouvelle condition pour vérifier si la commande existe
	if (!is_builtin(cmd->args[0]))
	{
		path = find_path(cmd->args[0], envp);
		if (!path)
		{
			// La commande n'existe pas, libérer la mémoire et sortir
			print_command_not_found(cmd->args[0]);
			g_global.exit_status = 127;
			free_array(cmd->args);
			free(cmd);
			return ;
		}
		free(path); // Libérer le chemin trouvé
	}
	
	if (is_builtin(cmd->args[0]))
	{
		if (contains_redirection(tokens) > 0)
		{
			saved_stdout = dup(STDOUT_FILENO);
			saved_stdin = dup(STDIN_FILENO);
			if (handle_redirections(tokens) == 0)
				result = run_builtin(cmd->args, envp);
			else
				result = 1;
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdout);
			close(saved_stdin);
		}
		else
			result = run_builtin(cmd->args, envp);
		g_global.exit_status = result;
	}
	else
	{
		setup_child_signals();
		first_child(tokens, envp);
		setup_interactive_signals();
	}
	free_array(cmd->args);
	free(cmd);
}

void	process_line(char *line, t_env *envp)
{
	t_token		*tokens;
	t_pipeline	*pipeline;
	t_token		*current;
	int			has_command;
	t_token		*temp;
	int			saved_stdout;
	int			saved_stdin;

	tokens = NULL;
	pipeline = NULL;
	tokens = lexer(line);
	if (!tokens)
		return ;
	if (check_syntax_errors(tokens) == -1)
	{
		free_tokens(&tokens);
		return ;
	}
	current = tokens;
	has_command = 0;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
		{
			temp = tokens;
			while (temp && temp->next != current)
				temp = temp->next;
			if (!temp || !is_redirection(temp))
			{
				has_command = 1;
				break ;
			}
		}
		current = current->next;
	}
	if (!has_command && contains_redirection(tokens) > 0)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		if (handle_redirections(tokens) == 0)
			g_global.exit_status = 0;
		else
			g_global.exit_status = 1;
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		free_tokens(&tokens);
		return ;
	}
	pipeline = create_pipeline(tokens);
	if (!pipeline)
	{
		free_tokens(&tokens);
		return ;
	}
	if (pipeline->cmd_count == 1)
		execute_single_command(tokens, envp);
	else
	{
		int	pipeline_result;

		pipeline_result = execute_pipeline(pipeline, envp, tokens);
		if (pipeline_result != -1)
		{
			g_global.exit_status = pipeline_result;
		}
	}
	free_tokens(&tokens);
	free_pipeline(pipeline);
	if (g_global.shell_status == 1)
		return ;
}

void	init_global(t_env *envp)
{
	g_global.env = envp;
	g_global.shell_status = 0;
	g_global.exit_status = 0;
	g_global.signal_received = 0;
	g_global.child_pid = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_env	envp;
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	memset(&envp, 0, sizeof(t_env));
	init_env(&envp, env);
	init_global(&envp);
	setup_interactive_signals();
	while (1)
	{
		line = prompt_and_read();
		if (!line)
			break ;
		process_line(line, &envp);
		free(line);
		if (g_global.shell_status == 1)
		{
			rl_clear_history();
			free_env(&envp);
			exit(g_global.exit_status);
		}
	}
	rl_clear_history();
	free_env(&envp);
	return (0);
}
