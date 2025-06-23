/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:17:37 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:15:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"
#include "../../includes/built_in.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	exit_shell(char **args)
{
	long	exit_code;
	int		i;

	i = 1;
	printf("exit\n");
	if (args[i] && ft_strcmp(args[i], "--") == 0)
		i++;
	if (args[i])
	{
		if (!is_numeric(args[i]))
		{
			printf("exit: %s: numeric argument required\n", args[i]);
			g_global.exit_status = 2;
			g_global.shell_status = 1;
			return (2);
		}
		if (args[i + 1])
			return (printf("exit: too many arguments\n"), 1);
		exit_code = ft_atol(args[i]);
		g_global.exit_status = (unsigned char)exit_code;
	}
	else
		g_global.exit_status = 0;
	g_global.shell_status = 1;
	return (g_global.exit_status);
}
