/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:04:49 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:11:08 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built_in.h"

int	print_invalid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || str[0] == '=')
		return (print_invalid_identifier(str));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (print_invalid_identifier(str));
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=')
				return (print_invalid_identifier(str));
			break ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (print_invalid_identifier(str));
		i++;
	}
	return (1);
}

int	find_env_var_index(char **env, char *var)
{
	int		i;
	int		len;
	char	*name;

	if (!env || !var)
		return (-1);
	name = get_var_name(var);
	if (!name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0
			&& (env[i][len] == '=' || env[i][len] == '\0'))
		{
			free(name);
			return (i);
		}
		i++;
	}
	free(name);
	return (-1);
}

char	*get_current_value(char **env, char *var_name)
{
	int		i;
	int		len;
	char	*value;

	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			value = ft_strdup(env[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}
