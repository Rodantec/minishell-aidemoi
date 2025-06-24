/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:47:27 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 16:47:27 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
