/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:58:59 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:59:40 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_and_expand_word(char *input,
	int start, int end, int should_expand)
{
	char			*word;
	char			*processed_word;
	extern t_global	g_global;

	word = ft_substr(input, start, end - start);
	if (!word)
		return (NULL);
	if (should_expand)
	{
		processed_word = process_quotes_and_expand(word, g_global.env);
		free(word);
		return (processed_word);
	}
	return (word);
}

int	count_tokens(t_token *tokens)
{
	t_token	*current;
	int		count;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
