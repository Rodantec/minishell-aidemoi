/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:00:50 by rodantec          #+#    #+#             */
/*   Updated: 2024/10/22 14:37:28 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *b, int c, int len)
{
	unsigned char	*a;
	int				i;

	i = 0;
	a = (unsigned char *)b;
	while (len > i)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
