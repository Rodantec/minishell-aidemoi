/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 15:17:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	print_env(t_env *envp)
{
	int	i;

	i = 0;
	if (!envp->env)
		return (1);
	while (envp->env[i])
	{
		printf("%s\n", envp->env[i]);
		i++;
	}
	return (0);
}

char	*join_if_append(char *value, char *current)
{
	char	*tmp;

	if (current && value)
	{
		tmp = ft_strjoin(current, value);
		free(value);
		free(current);
		return (tmp);
	}
	if (current)
		return (current);
	return (value);
}
