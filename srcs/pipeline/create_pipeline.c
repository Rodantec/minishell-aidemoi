/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:10:41 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipeline.h"

t_token	*create_redirection_pair(t_token *current, t_token **head,
	t_token **tail)
{
	t_token	*new_redir;
	t_token	*new_file;

	new_redir = create_token(current->type, current->value);
	if (!new_redir)
		return (*head);
	new_file = create_token(current->next->type, current->next->value);
	if (!new_file)
	{
		free(new_redir->value);
		free(new_redir);
		return (*head);
	}
	new_redir->next = new_file;
	if (!*head)
	{
		*head = new_redir;
		*tail = new_file;
	}
	else
	{
		(*tail)->next = new_redir;
		*tail = new_file;
	}
	return (current->next);
}

t_token	*extract_command_redirections(t_token *cmd_start)
{
	t_token	*redir_head;
	t_token	*redir_tail;
	t_token	*current;

	redir_head = NULL;
	redir_tail = NULL;
	current = cmd_start;
	while (current && current->type != TOKEN_PIPE)
	{
		if ((is_redirection(current))
			&& current->next && current->next->type == TOKEN_WORD)
			current = create_redirection_pair(current,
					&redir_head, &redir_tail);
		current = current->next;
	}
	return (redir_head);
}

t_command	*init_single_command(t_token *cmd_start)
{
	t_command	*cmd;
	int			arg_count;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->redirections = NULL;
	arg_count = count_args(cmd_start);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	if (!copy_command_args_only(cmd, cmd_start))
	{
		free(cmd);
		ft_putstr_fd("bite: ", STDERR_FILENO);
		return (NULL);
	}
	cmd->redirections = extract_command_redirections(cmd_start);
	return (cmd);
}

t_pipeline	*init_pipeline_struct(int cmd_count)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = malloc(sizeof(t_command *) * cmd_count);
	if (!pipeline->commands)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->cmd_count = cmd_count;
	pipeline->pipes = NULL;
	return (pipeline);
}

t_pipeline	*create_pipeline(t_token *tokens)
{
	t_pipeline	*pipeline;
	t_token		*current;
	t_token		*cmd_start;
	int			i;

	if (!tokens || error_token(tokens) == -1)
		return (NULL);
	pipeline = init_pipeline_struct(count_commands(tokens));
	if (!pipeline)
		return (NULL);
	i = 0;
	current = tokens;
	cmd_start = current;
	while (i < pipeline->cmd_count)
	{
		pipeline->commands[i] = init_single_command(cmd_start);
		while (current && current->type != TOKEN_PIPE)
			current = current->next;
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
		cmd_start = current;
		i++;
	}
	return (pipeline);
}
