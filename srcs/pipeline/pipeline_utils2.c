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
#include "../../includes/exec.h"
#include "../../includes/built_in.h"
#include "../../includes/pipeline.h"

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

void	execute_external_command(t_command *cmd, t_env *envp, t_token *token, t_pipeline *pipeline, t_token *token_lexer)
{
	char	*path;

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->args[0], STDERR_FILENO);
		free_tokens(&token);
		free_tokens(&token_lexer);
		free_env(envp);
		free_pipeline(pipeline);
		exit(127) ;
	}
	execve(path, cmd->args, envp->env);
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

void	handle_builtin_execution(t_command *cmd, t_env *envp,
	t_pipeline *pipeline, t_token *token, t_token *token_lexer)
{
	int	builtin_result;

	builtin_result = run_builtin(cmd->args, envp);
	if (builtin_result != -1)
	{
		if (pipeline && pipeline->pipes)
			close_pipes(pipeline->pipes, pipeline->cmd_count);
		free(token->value);
		free(token);
		exit(builtin_result);
	}
	if (pipeline && pipeline->pipes)
		close_pipes(pipeline->pipes, pipeline->cmd_count);
	execute_external_command(cmd, envp, token, pipeline, token_lexer);
}

void	execute_pipeline_command(t_command *cmd, int cmd_index,
	t_pipeline *pipeline, t_env *envp, t_token *token_lexer)
{
	t_token	*token;
	int		saved_fds[2];

	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	setup_command_io(pipeline, cmd_index, saved_fds);
	if (cmd->redirections && handle_redirections(cmd->redirections, envp, token_lexer, pipeline) == -1)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[0]);
		close(saved_fds[1]);

		if (pipeline && pipeline->pipes)
			close_pipes(pipeline->pipes, pipeline->cmd_count);
		exit(1);
	}
	close(saved_fds[0]);
	close(saved_fds[1]);
	token = create_command_token(cmd);
	if (!token)
	{
		if (pipeline && pipeline->pipes)
			close_pipes(pipeline->pipes, pipeline->cmd_count);
		exit(1);
	}
	handle_builtin_execution(cmd, envp, pipeline, token, token_lexer);
	free_pipeline(pipeline);
	free_cmd(cmd);
}
