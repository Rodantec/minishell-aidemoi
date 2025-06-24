/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:46:39 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:57:38 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_token(t_token *token)
{
	while (token)
	{
		if (is_redirection(token)
			&& (!token->next || token->next->type != TOKEN_WORD))
		{
			if (token->next)
				print_syntax_error_token(token->next->value);
			else
				print_syntax_error_token(NULL);
			return (-1);
		}
		token = token->next;
	}
	return (0);
}

int	save_file_descriptors(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	if (*in == -1)
	{
		perror("dup stdin");
		return (-1);
	}
	*out = dup(STDOUT_FILENO);
	if (*out == -1)
	{
		perror("dup stdout");
		close(*in);
		return (-1);
	}
	return (0);
}

void	restore_file_descriptors(int in, int out)
{
	if (in != -1)
	{
		if (dup2(in, STDIN_FILENO) == -1)
			perror("restore stdin");
		close(in);
	}
	if (out != -1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			perror("restore stdout");
		close(out);
	}
}

int	is_quoted_delimiter(char *delim)
{
	int	len;

	if (!delim)
		return (0);
	len = ft_strlen(delim);
	if (len >= 2)
	{
		if ((delim[0] == '\'' && delim[len - 1] == '\'')
			|| (delim[0] == '"' && delim[len - 1] == '"'))
			return (1);
	}
	return (0);
}

char	*remove_quotes_from_delimiter(char *delim)
{
	int		len;

	if (!is_quoted_delimiter(delim))
		return (ft_strdup(delim));
	len = ft_strlen(delim);
	return (ft_substr(delim, 1, len - 2));
}
