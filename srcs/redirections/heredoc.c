/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:17:33 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/23 11:50:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*generate_heredoc_basename(void)
{
	char	*base;

	base = ft_strdup("/tmp/.heredoc_0");
	return (base);
}

char	*create_heredoc_filename(void)
{
	char	*filename;

	filename = generate_heredoc_basename();
	if (!filename)
		return (NULL);
	return (filename);
}

int	is_delimiter(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	write_heredoc_content(int fd, char *delimiter,
		int should_expand, t_env *envp)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("\nwarning: here-document delimited by end-of-file\n",
				2);
			break ;
		}
		if (is_delimiter(line, delimiter))
			break ;
		if (should_expand)
		{
			expanded_line = expand_variables(line, envp);
			if (expanded_line)
			{
				ft_putendl_fd(expanded_line, fd);
				if (expanded_line != line)
					free(expanded_line);
			}
			else
				ft_putendl_fd(line, fd);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

char	*handle_heredoc(char *delimiter, int should_expand, t_env *envp)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_filename();
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(filename);
		return (NULL);
	}
	write_heredoc_content(fd, delimiter, should_expand, envp);
	close(fd);
	return (filename);
}

void	cleanup_heredoc(char *filename)
{
	if (filename)
	{
		unlink(filename);
		free(filename);
	}
}
