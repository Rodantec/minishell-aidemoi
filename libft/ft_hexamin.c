/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexamin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:37:57 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/17 17:50:09 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexamin(int n)
{
	char			*str;
	int				j;
	unsigned int	ln;
	int				rest;

	ln = (unsigned int)n;
	j = ft_size_n_hexa(ln);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	str[j] = '\0';
	while (j > 0)
	{
		rest = ln % 16;
		if (rest <= 9)
			str[--j] = rest + '0';
		else
			str[--j] = rest - 10 + 'a';
		ln /= 16;
	}
	j = ft_printstr_fd(str, 1);
	free(str);
	return (j);
}
/*int main ()
{
	printf("%s\n", ft_hexamin(50));
	printf("%x", 50);
}*/
