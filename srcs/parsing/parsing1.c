/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:09:17 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 17:09:17 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_line(char *line)
{
	t_command	*cmd;
	t_token		*tokens;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		free_tokens(&tokens);
		return (NULL);
	}
	cmd->args = tokens_to_args(tokens);
	free_tokens(&tokens);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
