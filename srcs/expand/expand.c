/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.42.fr>             +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:19:18 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/22 11:13:17 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_var_name(char *str)
{
	int		i;
	int		start;
	int		len;
	char	*var_name;

	if (!str || !*str)
		return (NULL);
	i = 0;
	if (str[i] == '$')
		i++;
	start = i;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	return (var_name);
}

char	*get_env_value(char *var_name, t_env *envp)
{
	int		i;
	int		j;
	char	*value;

	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_global.exit_status));
	if (!envp || !envp->env)
		return (NULL);
	i = 0;
	while (envp->env[i])
	{
		j = 0;
		while (envp->env[i][j] && envp->env[i][j] != '=')
			j++;
		if (ft_strncmp(envp->env[i], var_name, j) == 0 && var_name[j] == '\0')
		{
			value = ft_strdup(envp->env[i] + j + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*handle_expansion(char *prefix, char *var_value, char *suffix)
{
	char	*temp;
	char	*result;

	if (var_value)
	{
		temp = ft_strjoin(prefix, var_value);
		result = ft_strjoin(temp, suffix);
		free(temp);
	}
	else
		result = ft_strjoin(prefix, suffix);
	free(prefix);
	free(suffix);
	free(var_value);
	return (result);
}

char	*expand_once(char *arg, t_env *envp)
{
	char	*dollar_pos;
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;

	dollar_pos = ft_strchr(arg, '$');
	if (!dollar_pos)
		return (ft_strdup(arg));
	var_name = extract_var_name(dollar_pos);
	if (!var_name)
		return (ft_strdup(arg));
	var_value = get_env_value(var_name, envp);
	prefix = ft_substr(arg, 0, dollar_pos - arg);
	suffix = ft_strdup(dollar_pos + ft_strlen(var_name) + 1);
	free(var_name);
	return (handle_expansion(prefix, var_value, suffix));
}

char	*expand(char *arg, t_env *envp)
{
	char	*result;
	char	*dollar_pos;
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;
	char	*temp;

	if (!arg || !envp)
		return (ft_strdup(arg));
	result = ft_strdup(arg);
	if (!result)
		return (NULL);
	while ((dollar_pos = ft_strchr(result, '$')) != NULL)
	{
		var_name = extract_var_name(dollar_pos);
		if (!var_name)
			break;
		var_value = get_env_value(var_name, envp);
		prefix = ft_substr(result, 0, dollar_pos - result);
		suffix = ft_strdup(dollar_pos + ft_strlen(var_name) + 1);
		temp = handle_expansion(prefix, var_value, suffix);
		free(var_name);
		free(result);
		result = temp;
		if (!result)
			break;
	}
	return (result);
}
