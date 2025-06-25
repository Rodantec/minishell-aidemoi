/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/04 11:21:27 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_command_token(t_command *cmd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_WORD;
	token->value = ft_strdup(cmd->args[0]);
	token->next = NULL;
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

void	execute_external_command(t_command *cmd,
	t_minishell *minishell, t_token *token)
{
	char	*path;

	path = find_path(cmd->args[0], &minishell->env);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->args[0], STDERR_FILENO);
		free_tokens(&token);
		free_tokens(&minishell->tokens);
		free_env(&minishell->env);
		free_pipeline(minishell->pipeline);
		exit(127);
	}
	execve(path, cmd->args, minishell->env.env);
	free(path);
	perror("execve");
	exit(1);
}

void	setup_command_io(t_pipeline *pipeline, int cmd_index, int *saved_fds)
{
	if (pipeline && pipeline->pipes)
		setup_pipes(pipeline->pipes, cmd_index, pipeline->cmd_count);
	if (saved_fds[0] == -1 || saved_fds[1] == -1)
	{
		perror("dup");
		exit(1);
	}
}

void	handle_builtin_execution(t_command *cmd,
	t_minishell *minishell, t_token *token)
{
	int	builtin_result;

	builtin_result = run_builtin(cmd->args, &minishell->env);
	if (builtin_result != -1)
	{
		if (minishell->pipeline->pipes)
			close_pipes(minishell->pipeline->pipes,
				minishell->pipeline->cmd_count);
	//	printf("iciiiiiiiiiiiii");
		free(token->value);
		free(token);
		// Ajouter la libération complète avant exit
		free_tokens(&minishell->tokens);
		free_env(&minishell->env);
		free_pipeline(minishell->pipeline);
		exit(builtin_result);
	}
	if (minishell->pipeline->pipes)
		close_pipes(minishell->pipeline->pipes, minishell->pipeline->cmd_count);
	execute_external_command(cmd, minishell, token);
}

void	restore_fds_and_exit(int *saved_fds, t_minishell *minishell)
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
	if (minishell->pipeline->pipes)
		close_pipes(minishell->pipeline->pipes,
			minishell->pipeline->cmd_count);
	exit(1);
}
