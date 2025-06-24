/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:00:00 by lkiloul           #+#    #+#             */
/*   Updated: 2025/05/21 15:00:00 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_quote_char(char c, char *quote_type, int *in_quotes)
{
	if (!*in_quotes)
	{
		*in_quotes = 1;
		*quote_type = c;
		return (1);
	}
	else if (c == *quote_type)
	{
		*in_quotes = 0;
		*quote_type = 0;
		return (1);
	}
	return (0);
}

static void	copy_char_if_needed(char *str, char *result, int i, int *j)
{
	result[(*j)++] = str[i];
}

static int	should_skip_quote(char c, char *quote_type, int *in_quotes)
{
	if (c == '\'' || c == '"')
		return (process_quote_char(c, quote_type, in_quotes));
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote_type;
	int		in_quotes;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	quote_type = 0;
	while (str[i])
	{
		if (!should_skip_quote(str[i], &quote_type, &in_quotes))
			copy_char_if_needed(str, result, i, &j);
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*finalize_expansion(char *new_str, char *temp_word, int j)
{
	char	*suffix;
	char	*final;

	suffix = ft_strdup(temp_word + j);
	if (!suffix)
	{
		free(new_str);
		return (NULL);
	}
	final = ft_strjoin(new_str, suffix);
	free(new_str);
	free(suffix);
	return (final);
}
