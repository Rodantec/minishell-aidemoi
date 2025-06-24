/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:29:55 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 18:29:55 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_variable_replacement(char *current,
		char *temp_word, int i, t_env *envp)
{
	char	*result;

	result = process_dollar_sign(current, i, envp);
	if (!result)
		return (NULL);
	if (result != current && current != temp_word)
		free(current);
	return (result);
}

int	process_character(char *current, int i, char *quote_type, int *in_quotes)
{
	update_quote_state(current[i], quote_type, in_quotes);
	if (current[i] == '$' && *quote_type != '\'')
		return (1);
	return (0);
}

char	*scan_and_expand(char *current, char *temp_word, t_env *envp)
{
	int		i;
	int		in_quotes;
	char	quote_type;
	char	*result;

	i = 0;
	in_quotes = 0;
	quote_type = 0;
	while (current[i])
	{
		if (process_character(current, i, &quote_type, &in_quotes))
		{
			result = handle_variable_replacement(current, temp_word, i, envp);
			if (!result)
				return (NULL);
			if (result != current)
				return (result);
		}
		i++;
	}
	return (current);
}

char	*expand_variables(char *temp_word, t_env *envp)
{
	char	*current;
	char	*result;

	current = temp_word;
	while (1)
	{
		result = scan_and_expand(current, temp_word, envp);
		if (!result)
			return (NULL);
		if (result == current)
			break ;
		current = result;
	}
	return (current);
}

char	*process_quotes_and_expand(char *word, t_env *envp)
{
	char	*temp_word;
	char	*expanded;
	char	*result;

	if (!word)
		return (NULL);
	temp_word = ft_strdup(word);
	if (!temp_word)
		return (NULL);
	expanded = expand_variables(temp_word, envp);
	if (expanded != temp_word)
		free(temp_word);
	if (!expanded)
		return (NULL);
	result = remove_quotes(expanded);
	free(expanded);
	return (result);
}
