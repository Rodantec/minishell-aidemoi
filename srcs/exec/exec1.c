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

#include "../../includes/exec.h"
#include "minishell.h"

void	run_child_process(t_token *token, t_env *env)
{
	int	redirection_count;

	setup_child_signals();
	redirection_count = contains_redirection(token);
	if (redirection_count > 0)
	{
		if (handle_redirections(token) < 0)
			exit(1);
	}
	execute_cmd(token, env);
	perror("Error");
	exit(1);
}

void	first_child(t_token *token, t_env *env)
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
		run_child_process(token, env);
	g_global.child_pid = pid;
	g_global.shell_status = 1;
	setup_execution_signals();
	waitpid(pid, &status, WUNTRACED);
	setup_interactive_signals();
	g_global.child_pid = 0;
	g_global.shell_status = 0;
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
