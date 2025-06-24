/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/04 23:33:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_command_not_found(char *cmd)
{
	if (cmd)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd);
		g_global.exit_status = 127;
	}
}

void	print_syntax_error(void)
{
	fprintf(stderr, "minishell: syntax error\n");
	g_global.exit_status = 2;
}

void	print_syntax_error_token(char *token)
{
	if (token)
		fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
			token);
	else
		fprintf(stderr,
			"minishell: syntax error near unexpected token `newline'\n");
	g_global.exit_status = 2;
}

int	check_redirection_error(t_token *current)
{
	if ((is_redirection(current))
		&& (!current->next || current->next->type != TOKEN_WORD))
	{
		if (current->next && current->next->type != TOKEN_EOF)
			print_syntax_error_token(current->next->value);
		else
			print_syntax_error_token(NULL);
		return (-1);
	}
	return (0);
}

int	check_pipe_error(t_token *current)
{
	if (current->type == TOKEN_PIPE)
	{
		if (!current->next || current->next->type == TOKEN_EOF)
		{
			print_syntax_error_token(NULL);
			return (-1);
		}
		if (current->next->type == TOKEN_PIPE)
		{
			print_syntax_error_token("|");
			return (-1);
		}
	}
	return (0);
}
