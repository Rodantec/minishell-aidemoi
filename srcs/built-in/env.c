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

#include "../../includes/built_in.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../includes/minishell.h"

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

int	init_env_arrays(t_env *envp, char **env)
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
	envp->env = malloc(sizeof(char *) * (i + 1));
	if (!envp->env)
		return (1);
	envp->export = malloc(sizeof(char *) * (i + 1));
	if (!envp->export)
	{
		free(envp->env);
		return (1);
	}
	if (init_env_arrays(envp, env))
		return (1);
	if (env == default_env)
		free_array(default_env);
	return (0);
}
