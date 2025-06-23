/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:15:02 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 13:15:02 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"
#include <stdio.h>
#include <stdlib.h>

void	sort_env(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_var(char *var)
{
	char	*name;
	char	*value;
	int		i;

	name = get_var_name(var);
	if (!name)
		return ;
	printf("declare -x %s", name);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
	{
		value = get_var_value(var);
		printf("=\"%s\"", value);
		free(value);
	}
	printf("\n");
	free(name);
}

int	export_solo(t_env *envp)
{
	int	i;

	if (!envp->export)
	{
		envp->export = env_cpy(envp);
		if (!envp->export)
			return (1);
		envp->count_export = 0;
		while (envp->export[envp->count_export])
			envp->count_export++;
	}
	sort_env(envp->export, envp->count_export);
	i = 0;
	while (envp->export[i])
	{
		print_export_var(envp->export[i]);
		i++;
	}
	return (0);
}

int	export_var(t_env *envp, char **args)
{
	int	i;
	int	error;

	if (!args[1])
		return (export_solo(envp));
	i = 1;
	error = 0;
	while (args[i])
	{
		if (update_export_var(envp, args[i]))
			error = 1;
		else if (has_equals_sign(args[i]))
			update_env_var(envp, args[i]);
		i++;
	}
	return (error);
}
