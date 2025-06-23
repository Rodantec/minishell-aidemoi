/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:57:31 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:57:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <stdio.h>

int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_echo_args(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	echo(char **args)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (!args)
		return (-1);
	while (args[i] && is_n_option(args[i]))
	{
		no_newline = 1;
		i++;
	}
	print_echo_args(args, i);
	if (!no_newline)
		printf("\n");
	return (0);
}
