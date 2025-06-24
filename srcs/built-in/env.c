/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:17:42 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/21 14:46:42 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../includes/minishell.h"

int	init_count(t_env *envp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	envp->count_env = i;
	envp->count_export = i;
	return (i);
}

static int	init_env_part(t_env *envp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (init_env_vars(envp, env, i))
			return (free_array(envp->env), 1);
		i++;
	}
	envp->env[i] = NULL;
	return (0);
}

static int	init_export_part(t_env *envp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (init_export_vars(envp, i))
			return (free_array(envp->env), free_array(envp->export), 1);
		i++;
	}
	envp->export[i] = NULL;
	return (0);
}

static int	allocate_env_arrays(t_env *envp, int size)
{
	envp->env = malloc(sizeof(char *) * (size + 1));
	if (!envp->env)
		return (1);
	envp->export = malloc(sizeof(char *) * (size + 1));
	if (!envp->export)
		return (free(envp->env), 1);
	return (0);
}

int	init_env(t_env *envp, char **env)
{
	int		i;
	char	**default_env;

	default_env = NULL;
	if (!env || !env[0])
	{
		default_env = create_default_env();
		if (!default_env)
			return (1);
		env = default_env;
	}
	i = init_count(envp, env);
	if (allocate_env_arrays(envp, i))
		return (1);
	if (init_env_part(envp, env) || init_export_part(envp, env))
		return (1);
	if (env == default_env)
		free_array(default_env);
	return (0);
}
