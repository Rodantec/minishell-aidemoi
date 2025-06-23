/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:02:38 by rodantec          #+#    #+#             */
/*   Updated: 2024/10/23 09:44:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, int len)
{
	unsigned char		*ds;
	const unsigned char	*sr;

	ds = (unsigned char *)dst;
	sr = (const unsigned char *)src;
	if (src == dst || len == 0)
		return (dst);
	if (sr < ds)
	{
		while (len != 0)
		{
			len--;
			ds[len] = sr[len];
		}
	}
	else
	{
		while (len != 0)
		{
			*ds++ = *sr++;
			len--;
		}
	}
	return (dst);
}
