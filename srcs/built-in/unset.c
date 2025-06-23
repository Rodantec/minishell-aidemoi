/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:17:42 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/21 13:48:44 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/built_in.h"

void	remove_var(char **env, int *count, char *name)
{
	int	i;
	int	j;
	int	len;

	if (name[0] == '_')
		return ;
	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			(*count)--;
			return ;
		}
		i++;
	}
}

int	unset_var(char **args, t_env *envp)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) && args[i][0] != '_')
		{
			remove_var(envp->env, &envp->count_env, args[i]);
			remove_var(envp->export, &envp->count_export, args[i]);
		}
		i++;
	}
	return (0);
}
