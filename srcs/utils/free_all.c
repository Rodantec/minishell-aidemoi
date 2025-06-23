/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:48:46 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/21 12:00:26 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipeline.h"

void	free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->env)
		free_array(env->env);
	if (env->export)
		free_array(env->export);
	if (env->oldpwd)
		free(env->oldpwd);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

void	free_all(t_command *cmd, t_env *env, t_token *token)
{
	free_env(env);
	free_cmd(cmd);
	free_tokens(&token);
}

void	free_token_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	if (pipeline->commands)
	{
		i = 0;
		while (i < pipeline->cmd_count)
		{
			if (pipeline->commands[i])
			{
				if (pipeline->commands[i]->redirections)
					free_token_list(pipeline->commands[i]->redirections);
				free_cmd(pipeline->commands[i]);
			}
			i++;
		}
		free(pipeline->commands);
	}
	if (pipeline->pipes)
	{
		close_pipes(pipeline->pipes, pipeline->cmd_count);
		free(pipeline->pipes);
	}
	free(pipeline);
}

void	cleanup_minishell(void)
{
	rl_clear_history();
	if (g_global.env)
	{
		if (g_global.env->env)
			free_array(g_global.env->env);
		if (g_global.env->export)
			free_array(g_global.env->export);
	}
}
