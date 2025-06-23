/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:45:37 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/17 18:09:58 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0)
		return (0);
	if (s == NULL)
		s = "(null)";
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	ft_putstr_fd("bonjour monde", 2);
}*/
