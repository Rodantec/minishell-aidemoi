/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:21:57 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/30 10:42:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	replace_env_var(t_env *envp, int index, char *name, char *value)
{
	free(envp->env[index]);
	if (value)
		envp->env[index] = ft_strjoin3(name, "=", value);
	else
		envp->env[index] = ft_strjoin(name, "=");
	return (0);
}

int	add_env_var(t_env *envp, char *name, char *value)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (envp->count_env + 2));
	if (!new_env)
		return (1);
	i = -1;
	while (++i < envp->count_env)
		new_env[i] = ft_strdup(envp->env[i]);
	if (value)
		new_env[i] = ft_strjoin3(name, "=", value);
	else
		new_env[i] = ft_strjoin(name, "=");
	new_env[i + 1] = NULL;
	free_array(envp->env);
	envp->env = new_env;
	envp->count_env++;
	return (0);
}

static int	process_var_names(char *var, char **name, char **value)
{
	*name = get_var_name(var);
	*value = get_var_value(var);
	if (!*name)
	{
		if (*value)
			free(*value);
		return (1);
	}
	return (0);
}

static void	cleanup_vars(char *name, char *value)
{
	free(name);
	if (value)
		free(value);
}

int	update_env_var(t_env *envp, char *var)
{
	char	*name;
	char	*value;
	char	*current;
	int		index;
	int		result;

	if (!envp || !var)
		return (1);
	if (process_var_names(var, &name, &value) != 0)
		return (1);
	index = find_env_var_index(envp->env, var);
	if (has_plus_equals(var))
	{
		current = get_current_value(envp->env, name);
		value = join_if_append(value, current);
	}
	if (index >= 0)
		result = replace_env_var(envp, index, name, value);
	else
		result = add_env_var(envp, name, value);
	cleanup_vars(name, value);
	return (result);
}
