/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:59:32 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 16:59:32 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
