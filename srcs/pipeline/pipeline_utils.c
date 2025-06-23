/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:10:41 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipeline.h"

int	count_commands(t_token *tokens)
{
	t_token	*current;
	int		count;

	count = 1;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

int	count_args(t_token *cmd_start)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = cmd_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	copy_command_args_only(t_command *cmd, t_token *cmd_start)
{
	t_token	*tmp;
	int		j;

	j = 0;
	tmp = cmd_start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
		{
			cmd->args[j] = ft_strdup(tmp->value);
			if (!cmd->args[j])
				return (free_array(cmd->args), 0);
			j++;
		}
		else if (is_redirection(tmp))
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd->args[j] = NULL;
	return (1);
}
