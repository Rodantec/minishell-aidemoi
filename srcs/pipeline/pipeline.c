/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/23 11:15:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
#include "../../includes/built_in.h"
#include "../../includes/pipeline.h"

int	init_pipeline_execution(t_pipeline *pipeline, pid_t **pids)
{
	if (!pipeline || !pipeline->commands || pipeline->cmd_count < 1)
		return (-1);
	if (pipeline->cmd_count > 1)
	{
		pipeline->pipes = create_pipes(pipeline->cmd_count);
		if (!pipeline->pipes)
			return (-1);
	}
	*pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!*pids)
	{
		if (pipeline->pipes)
			close_pipes(pipeline->pipes, pipeline->cmd_count);
		return (-1);
	}
	return (0);
}

int	handle_fork_error(t_pipeline *pipeline, pid_t *pids, int i)
{
	while (--i >= 0)
		waitpid(pids[i], NULL, WUNTRACED);
	free(pids);
	if (pipeline->pipes)
		close_pipes(pipeline->pipes, pipeline->cmd_count);
	perror("fork");
	return (-1);
}

int	handle_child_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	wait_for_children(t_pipeline *pipeline, pid_t *pids)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	g_global.shell_status = 1;
	setup_execution_signals();
	while (i < pipeline->cmd_count)
	{
		if (waitpid(pids[i], &status, WUNTRACED) > 0)
		{
			if (WIFSTOPPED(status))
			{
				printf("\n[%d]+  Stopped\t\tcommand\n", pids[i]);
				last_status = 0;
			}
			else
				last_status = handle_child_status(status);
		}
		i++;
	}
	setup_interactive_signals();
	g_global.shell_status = 0;
	free(pids);
	return (last_status);
}

int	execute_pipeline(t_pipeline *pipeline, t_env *envp)
{
	pid_t	*pids;
	int		i;

	if (init_pipeline_execution(pipeline, &pids) == -1)
		return (-1);
	i = 0;
	while (i < pipeline->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (handle_fork_error(pipeline, pids, i));
		if (pids[i] == 0)
		{
			free(pids);
			execute_pipeline_command(pipeline->commands[i],
				i, pipeline, envp);
		}
		i++;
	}
	if (pipeline->pipes)
		close_pipes(pipeline->pipes, pipeline->cmd_count);
	pipeline->pipes = NULL;
	return (wait_for_children(pipeline, pids));
}
