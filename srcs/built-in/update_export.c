/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:01:46 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:00:43 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	replace_export_var(t_env *envp, int index, char *name, char *value)
{
	free(envp->export[index]);
	if (value)
		envp->export[index] = ft_strjoin3(name, "=", value);
	else
		envp->export[index] = ft_strdup(name);
	return (0);
}

int	add_export_var(t_env *envp, char *name, char *value)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (envp->count_export + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < envp->count_export)
	{
		new_env[i] = ft_strdup(envp->export[i]);
		i++;
	}
	if (value)
		new_env[i] = ft_strjoin3(name, "=", value);
	else
		new_env[i] = ft_strdup(name);
	new_env[i + 1] = NULL;
	free_array(envp->export);
	envp->export = new_env;
	envp->count_export++;
	return (0);
}

char	*handle_export_append(t_env *envp, char *name, char *value)
{
	char	*current;
	char	*combined;

	current = get_current_value(envp->export, name);
	if (current && value)
	{
		combined = ft_strjoin(current, value);
		free(current);
		free(value);
		return (combined);
	}
	if (current)
		return (current);
	return (value);
}

int	update_export_var(t_env *envp, char *var)
{
	char	*name;
	char	*value;
	int		index;
	int		result;

	if (!envp || !var || !is_valid_identifier(var))
		return (1);
	if (!envp->export)
		envp->export = env_cpy(envp);
	name = get_var_name(var);
	value = get_var_value(var);
	if (!name)
		return (1);
	if (has_plus_equals(var))
		value = handle_export_append(envp, name, value);
	index = find_env_var_index(envp->export, var);
	if (index >= 0)
		result = replace_export_var(envp, index, name, value);
	else
		result = add_export_var(envp, name, value);
	free(name);
	free(value);
	return (result);
}
