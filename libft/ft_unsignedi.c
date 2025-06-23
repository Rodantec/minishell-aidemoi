/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:21:16 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/17 18:09:58 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsignedi(unsigned int n)
{
	char	*str;
	int		j;
	int		i;
	long	ln;

	ln = n;
	j = ft_size_n_deci(n);
	i = 0;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	if (ln < 0)
	{
		ln *= -1;
		str[i++] = '-';
	}
	str[j] = '\0';
	while (i < j)
	{
		str[--j] = ((ln % 10) + '0');
		ln /= 10;
	}
	j = ft_printstr_fd(str, 1);
	free(str);
	return (j);
}
/*
int	main(void)
{
	printf("%u\n", 5454542185151);
	printf("%s", ft_printunsignedi(5454542185151));

}*/