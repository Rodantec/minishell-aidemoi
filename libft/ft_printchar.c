/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:39:16 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/17 18:09:23 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	write(fd, &c, 1);
	return (1);
}
/*
int	main(void)
{
	ft_putchar_fd('a', 0);
}*/
