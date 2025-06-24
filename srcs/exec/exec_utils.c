/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/24 15:20:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path_cut(t_env *env)
{
	int		i;
	char	**pathcut;

	i = 0;
	while (env->env[i] && ft_strnstr(env->env[i], "PATH=", 5) == NULL)
		i++;
	if (!env->env[i])
		return (NULL);
	pathcut = ft_split(env->env[i] + 5, ':');
	return (pathcut);
}
