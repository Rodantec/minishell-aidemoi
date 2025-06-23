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

int	check_syntax_errors(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens)
		return (0);
	current = tokens;
	prev = NULL;
	if (current->type == TOKEN_PIPE)
	{
		print_syntax_error_token("|");
		return (-1);
	}
	while (current && current->type != TOKEN_EOF)
	{
		if (check_redirection_error(current) == -1
			|| check_pipe_error(current) == -1)
			return (-1);
		prev = current;
		current = current->next;
	}
	if (prev && prev->type == TOKEN_PIPE)
		return (print_syntax_error_token(NULL), -1);
	return (0);
}
