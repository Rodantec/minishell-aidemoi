/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:45:56 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/17 18:07:12 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iitoa(int n)
{
	char	*str;
	int		j;
	int		i;
	long	ln;

	ln = n;
	j = ft_size_n_deci(ln);
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
int main (void)
{
	printf("%s\n",ft_itoa(100));
	printf("%i", 100);
}*/
