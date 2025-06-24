/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:09:51 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/23 12:00:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_word_token(char *word, t_token **tokens)
{
	t_token	*token;

	if (!word)
		return (-1);
	if (word[0] == '\0')
	{
		free(word);
		return (0);
	}
	token = create_token(TOKEN_WORD, word);
	free(word);
	if (!token)
		return (-1);
	add_token(tokens, token);
	return (0);
}

static int	get_expansion_flag(t_token **tokens)
{
	t_token	*last_token;

	last_token = *tokens;
	while (last_token && last_token->next)
		last_token = last_token->next;
	if (last_token && last_token->type == TOKEN_HEREDOC)
		return (0);
	return (1);
}

int	process_word(char *input, int *i, t_token **tokens)
{
	int		start;
	int		in_quotes;
	char	quote_type;
	char	*word;

	start = *i;
	in_quotes = 0;
	quote_type = 0;
	while (input[*i])
	{
		handle_quotes(input[*i], &in_quotes, &quote_type);
		if (check_word_end(input, *i, in_quotes))
			break ;
		(*i)++;
	}
	word = extract_and_expand_word(input,
			start, *i, get_expansion_flag(tokens));
	return (create_word_token(word, tokens));
}

int	process_redirection(char *input, int *i, t_token **tokens)
{
	int		result;
	t_token	*token;
	char	value[2];

	result = process_special_redirections(input, i, tokens);
	if (result == -1)
		return (-1);
	if (result == 0)
	{
		value[0] = input[*i];
		value[1] = '\0';
		token = create_token(get_token_type(input[*i]), value);
		if (!token)
			return (-1);
		add_token(tokens, token);
		(*i)++;
	}
	return (0);
}

int	process_pipe(char *input, int *i, t_token **tokens)
{
	t_token	*token;

	(void)input;
	token = create_token(TOKEN_PIPE, "|");
	if (!token)
		return (-1);
	add_token(tokens, token);
	(*i)++;
	return (0);
}
