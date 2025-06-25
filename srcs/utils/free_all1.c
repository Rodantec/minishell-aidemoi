/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:46:27 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 16:46:27 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// SUPPRIMER cette section qui cause le double free
	// if (pipeline->pipes)
	// {
	//     free(pipeline->pipes);
	//     pipeline->pipes = NULL;
	// }
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
