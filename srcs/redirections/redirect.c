/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:58:48 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/21 12:07:52 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open <");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		perror("dup2 <");
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output_append(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open >>");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		perror("dup2 >>");
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output_trunc(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open >");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		perror("dup2 >");
		return (-1);
	}
	close(fd);
	return (0);
}

int	contains_redirection(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (is_redirection(current))
			count++;
		current = current->next;
	}
	return (count);
}

int	handle_redirections(t_token *token, t_env *env,
	t_token *token_lexer, t_pipeline *pipeline)

{
	int		stdin_backup;
	int		stdout_backup;
	t_token	*current;

	if (!token)
		return (0);
	if (save_file_descriptors(&stdin_backup, &stdout_backup) == -1)
		return (-1);
	current = token;
	while (current)
	{
		if (is_redirection(current))
		{
			if (apply_single_redirection(current,
					env, token_lexer, pipeline) == -1)
				return (restore_file_descriptors(stdin_backup, stdout_backup),
					-1);
			current = current->next;
		}
		else
			current = current->next;
	}
	close(stdin_backup);
	close(stdout_backup);
	return (0);
}
