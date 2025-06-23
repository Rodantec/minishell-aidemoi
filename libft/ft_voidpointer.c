/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_voidpointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:21:24 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/17 18:09:58 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*init_str(int size)
{
	char	*str;

	str = malloc(sizeof(char) * (size + 3));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	str[size + 2] = '\0';
	return (str);
}

int	ft_voidpointer(void *ptr)
{
	char			*str;
	int				size;
	unsigned long	ln;
	int				rest;

	ln = (unsigned long)ptr;
	size = ft_size_n_hexa(ln);
	str = init_str(size);
	if (!str)
		return (0);
	while (size > 0)
	{
		rest = ln % 16;
		if (rest <= 9)
			str[size + 1] = rest + '0';
		else
			str[size + 1] = rest - 10 + 'a';
		ln /= 16;
		size--;
	}
	size = ft_printstr_fd(str, 1);
	free(str);
	return (size);
}
