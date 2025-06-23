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
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_type = str[i];
			}
			else if (str[i] == quote_type)
			{
				in_quotes = 0;
				quote_type = 0;
			}
			else
				result[j++] = str[i];
		}
		else
			result[j++] = str[i];
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

int	find_var_end(char *str, int start)
{
	int	j;

	j = start + 1;
	if (str[j] == '?')
		return (j + 1);
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	return (j);
}

char	*replace_variable(char *temp_word, int i, t_env *envp)
{
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*new_str;
	int		j;

	var_name = extract_var_name(temp_word + i);
	if (!var_name)
		return (ft_strdup(temp_word));
	var_value = get_env_value(var_name, envp);
	prefix = ft_substr(temp_word, 0, i);
	if (!prefix)
	{
		free(var_name);
		free(var_value);
		return (NULL);
	}
	if (var_value)
	{
		new_str = ft_strjoin(prefix, var_value);
		free(var_value);
	}
	else
		new_str = ft_strdup(prefix);
	free(prefix);
	free(var_name);
	if (!new_str)
		return (NULL);
	j = find_var_end(temp_word, i);
	return (finalize_expansion(new_str, temp_word, j));
}

char	*expand_variables(char *temp_word, t_env *envp)
{
	int		i;
	int		in_quotes;
	char	quote_type;
	char	*result;
	char	*current;

	current = temp_word;
	while (1)
	{
		i = 0;
		in_quotes = 0;
		quote_type = 0;
		while (current[i])
		{
			if ((current[i] == '\'' || current[i] == '"')
				&& (!in_quotes || current[i] == quote_type))
			{
				if (in_quotes == 1)
				{
					in_quotes = 0;
					quote_type = 0;
				}
				else
				{
					in_quotes = 1;
					quote_type = current[i];
				}
			}
			if (current[i] == '$' && quote_type != '\'')
			{
				if (current[i + 1] == '\0'
					|| !(ft_isalnum(current[i + 1]) || current[i + 1] == '_'
						|| current[i + 1] == '?'))
				{
					i++;
					continue ;
				}
				result = replace_variable(current, i, envp);
				if (!result)
					return (NULL);
				if (current != temp_word)
					free(current);
				current = result;
				break ;
			}
			i++;
		}
		if (current[i] == '\0')
			break ;
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
