/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:54:42 by rodantec          #+#    #+#             */
/*   Updated: 2024/10/23 09:56:21 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(s);
	k = 0;
	while (s[i] && ft_checkset(s[i], set))
		i++;
	while (i < j && ft_checkset(s[j - 1], set))
		j--;
	str = malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	while (i < j)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}
