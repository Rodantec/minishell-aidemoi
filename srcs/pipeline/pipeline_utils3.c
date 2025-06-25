/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:04:32 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 17:04:32 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_and_exit(t_minishell *minishell)
{
	if (minishell->pipeline->pipes)
		close_pipes(minishell->pipeline->pipes,
			minishell->pipeline->cmd_count);
	exit(1);
}

void	execute_pipeline_command(t_command *cmd,
			int cmd_index, t_minishell *minishell)
{
	t_token	*token;
	int		saved_fds[2];

	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	setup_command_io(minishell->pipeline, cmd_index, saved_fds);
	if (cmd->redirections && handle_redirections(cmd->redirections,
			&minishell->env, minishell->tokens, minishell->pipeline) == -1)
		restore_fds_and_exit(saved_fds, minishell);
	close(saved_fds[0]);
	close(saved_fds[1]);
	token = create_command_token(cmd);
	if (!token)
		cleanup_and_exit(minishell);
	handle_builtin_execution(cmd, minishell, token);
	free_pipeline(minishell->pipeline);
	free_cmd(cmd);
}
