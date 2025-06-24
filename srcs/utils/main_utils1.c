/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:41:52 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 17:41:52 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_and_read(void)
{
	char	*line;

	g_global.signal_received = 0;
	line = readline("minishell> ");
	if (!line)
	{
		if (g_global.signal_received == SIGINT)
		{
			g_global.signal_received = 0;
			return (ft_strdup(""));
		}
		if (g_global.shell_status == 0)
		{
			printf("exit\n");
			exit(g_global.exit_status);
		}
		return (NULL);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

int	find_command_token(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
			return (1);
		current = current->next;
	}
	return (0);
}
