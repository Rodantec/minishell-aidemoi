/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:10:41 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
#include "../../includes/built_in.h"
#include "../../includes/pipeline.h"

void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
			pipes[i] = NULL;  // Ajout de cette ligne
		}
		i++;
	}
	//free(pipes);
}

int	**init_pipe_array(int cmd_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = init_pipe_array(cmd_count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			while (i >= 0)
				free(pipes[i--]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	setup_pipes(int **pipes, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(pipes[cmd_index - 1][0]);
	}
	if (cmd_index < cmd_count - 1)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(pipes[cmd_index][1]);
	}
}
