/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:04:49 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:11:08 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"
#include "../../includes/minishell.h"

char	*update_shlvl(char **env)
{
	char	*shlvl_str;
	int		shlvl;
	char	*result;
	int		i;

	shlvl = 1;
	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			{
				shlvl = ft_atoi(env[i] + 6) + 1;
				break ;
			}
			i++;
		}
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (NULL);
	result = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	return (result);
}

char	**create_default_env(void)
{
	char	**env;
	char	*pwd;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(env);
		return (NULL);
	}
	env[0] = ft_strjoin3("PWD", "=", pwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	free(pwd);
	if (!env[0] || !env[1] || !env[2])
	{
		free_array(env);
		return (NULL);
	}
	return (env);
}

int	init_env_vars(t_env *envp, char **env, int i)
{
	char	*shlvl;

	if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
	{
		shlvl = update_shlvl(env);
		if (!shlvl)
			return (1);
		envp->env[i] = shlvl;
	}
	else
	{
		envp->env[i] = ft_strdup(env[i]);
		if (!envp->env[i])
			return (1);
	}
	return (0);
}

int	init_export_vars(t_env *envp, int i)
{
	if (!envp->env[i])
		return (1);
	envp->export[i] = ft_strdup(envp->env[i]);
	if (!envp->export[i])
		return (1);
	return (0);
}

char	**env_cpy(t_env *envp)
{
	int		i;
	int		size;
	char	**cpy_env;

	if (!envp->env)
		return (NULL);
	size = envp->count_env;
	cpy_env = malloc(sizeof(char *) * (size + 1));
	if (!cpy_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		cpy_env[i] = ft_strdup(envp->env[i]);
		i++;
	}
	cpy_env[i] = NULL;
	return (cpy_env);
}
