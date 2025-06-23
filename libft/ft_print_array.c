/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/15 10:50:36 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/15 10:53:19 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (1);
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return (0);
}
