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

t_global	g_global = {0};

void	handle_redir_only(t_token *tokens, t_env *envp)
{
	int	result;
	int	saved_stdin;
	int	saved_stdout;

	result = 0;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redirections(tokens, envp, tokens, NULL) == 0)
		result = 0;
	else
		result = 1;
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	g_global.exit_status = result;
}

int	check_and_handle_path(t_command *cmd, t_env *envp)
{
	char	*path;

	if (!is_builtin(cmd->args[0]))
	{
		path = find_path(cmd->args[0], envp);
		if (!path)
		{
			print_command_not_found(cmd->args[0]);
			g_global.exit_status = 127;
			free_array(cmd->args);
			free(cmd);
			return (0);
		}
		free(path);
	}
	return (1);
}

void	handle_builtin_cmd(t_token *tokens, t_command *cmd, t_env *envp)
{
	int	result;
	int	saved_stdout;
	int	saved_stdin;

	if (contains_redirection(tokens) > 0)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		if (handle_redirections(tokens, envp, tokens, NULL) == 0)
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

void	execute_single_command(t_token *tokens, t_env *envp,t_pipeline *pipeline)

{
	t_command	*cmd;

	if (!find_command_token(tokens))
	{
		if (contains_redirection(tokens) > 0)
			handle_redir_only(tokens, envp);
		return ;
	}
	if (init_command(tokens, &cmd) < 0)
		return ;
	if (!check_and_handle_path(cmd, envp))
		return ;
	if (is_builtin(cmd->args[0]))
		handle_builtin_cmd(tokens, cmd, envp);
	else
	{
		setup_child_signals();
		first_child(tokens, envp, cmd, pipeline);
		setup_interactive_signals();
	}
	free_array(cmd->args);
	free(cmd);
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
	return (free_env(&envp), 0);
}
