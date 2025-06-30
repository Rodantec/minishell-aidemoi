/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:04:16 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/23 12:15:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_child_process(t_token *token, t_env *env, t_command *cmd, t_pipeline *pipeline)
{
	int	redirection_count;

	setup_child_signals();
	redirection_count = contains_redirection(token);
	if (redirection_count > 0)
	{
		if (handle_redirections(token, env, token, NULL) < 0)
		{
			free_pipeline(pipeline);
			free_cmd(cmd);
			exit(1);
		}
	}
	execute_cmd(token, env);
	perror("Error");
	exit(1);
}

static void	process_child_status(int status, pid_t pid)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_global.exit_status = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_global.exit_status = 131;
	}
	else if (WIFSTOPPED(status))
	{
		printf("\n[%d]+  Stopped\t\t%s\n", pid, "command");
		g_global.exit_status = 0;
	}
	else
		g_global.exit_status = WEXITSTATUS(status);
}

void	first_child(t_token *token, t_env *env, t_command *cmd, t_pipeline *pipeline)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (pid == 0)
		run_child_process(token, env, cmd, pipeline);
	g_global.child_pid = pid;
	g_global.shell_status = 1;
	setup_execution_signals();
	waitpid(pid, &status, WUNTRACED);
	setup_interactive_signals();
	g_global.child_pid = 0;
	g_global.shell_status = 0;
	process_child_status(status, pid);
}
