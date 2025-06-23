/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:45:56 by rodantec          #+#    #+#             */
/*   Updated: 2024/10/25 12:30:34 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size_n(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		j;
	int		i;
	long	ln;

	ln = n;
	j = ft_size_n(n);
	i = 0;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
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
	return (str);
}
/*#include <stdio.h>

int main (void)
{
	printf("%s",ft_itoa(15));
}*/
