/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:42:02 by rodantec          #+#    #+#             */
/*   Updated: 2024/10/25 15:52:23 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checksep(char c, char b)
{
	if (b == c)
		return (1);
	return (0);
}

int	countword(char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && checksep(str[i], c))
			i++;
		if (str[i] && !checksep(str[i], c))
		{
			word++;
			while (str[i] && !checksep(str[i], c))
				i++;
		}
	}
	return (word);
}

char	*makeword(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*word;

	i = 0;
	j = 0;
	k = 0;
	while (s[j] && checksep(s[j], c))
		j++;
	while (s[i + j] && !checksep(s[i + j], c))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	while (i > k)
	{
		word[k] = s[j + k];
		k++;
	}
	word[i] = '\0';
	return (word);
}

void	*ft_freemem(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**words;

	j = 0;
	words = (char **)malloc(sizeof(char *) * (countword((char *)s, c) + 1));
	if (!words)
		return (NULL);
	while (*s)
	{
		while (checksep(*s, c))
			s++;
		if (*s && !checksep(*s, c))
		{
			words[j] = makeword(s, c);
			if (!words[j])
				return (ft_freemem(words));
			j++;
		}
		while (*s && !checksep(*s, c))
			s++;
	}
	words[j] = NULL;
	return (words);
}

/*
#include <stdio.h>

int	main(void)
{
	int i = 0;
	char *str = "aba";
	char c = 'b';
	char **words = ft_split(str, c);

	while (words[i] != NULL)
	{
		printf("%s\n", words[i]);
		free(words[i]);
		i++;
	}
	free(words);

	return (0);
}*/
