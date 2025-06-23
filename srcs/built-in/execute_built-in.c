/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built-in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:20:51 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/23 12:30:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"
#include "../../includes/minishell.h"

int	run_builtin(char **args, t_env *envp)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd(args, envp));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (print_env(envp));
	if (ft_strcmp(args[0], "export") == 0)
		return (export_var(envp, args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (unset_var(args, envp));
	if (ft_strcmp(args[0], "exit") == 0)
		return (exit_shell(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	return (-1);
}

int	init_command(t_token *token, t_command **cmd)
{
	if (!token || token->type != TOKEN_WORD)
		return (-1);
	*cmd = malloc(sizeof(t_command));
	if (!*cmd)
		return (-1);
	(*cmd)->args = tokens_to_args(token);
	if (!(*cmd)->args || !(*cmd)->args[0])
	{
		free(*cmd);
		return (-1);
	}
	return (0);
}

int	save_std_fds(int *saved_stdout, int *saved_stdin)
{
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
		return (-1);
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		close(*saved_stdout);
		return (-1);
	}
	return (0);
}

void	restore_fds(int saved_stdout, int saved_stdin)
{
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

int	execute_builtin(t_token *token, t_env *envp)
{
	t_command	*cmd;
	int			result;
	int			saved_stdout;
	int			saved_stdin;

	saved_stdout = -1;
	saved_stdin = -1;
	if (init_command(token, &cmd) < 0)
		return (-1);
	if (save_std_fds(&saved_stdout, &saved_stdin) < 0)
	{
		free(cmd);
		return (-1);
	}
	if (contains_redirection(token) > 0)
	{
		if (handle_redirections(token) < 0)
		{
			restore_fds(saved_stdout, saved_stdin);
			free_array(cmd->args);
			free(cmd);
			return (1);
		}
	}
	result = run_builtin(cmd->args, envp);
	restore_fds(saved_stdout, saved_stdin);
	free_array(cmd->args);
	free(cmd);
	return (result);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (0);
}
