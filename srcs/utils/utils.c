/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:39:42 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:08:55 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built_in.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	has_equals_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	has_plus_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var_value(char *str)
{
	int		i;
	int		start;
	char	*value;

	if (!has_equals_sign(str))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
		i++;
	if (str[i] == '+')
		i++;
	start = ++i;
	while (str[i])
		i++;
	value = malloc(sizeof(char) * (i - start + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[start + i])
	{
		value[i] = str[start + i];
		i++;
	}
	value[i] = '\0';
	return (value);
}
