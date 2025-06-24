/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:32:05 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 18:32:05 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_prefix_value(char *prefix, char *var_value)
{
	char	*new_str;

	if (var_value)
	{
		new_str = ft_strjoin(prefix, var_value);
		free(var_value);
	}
	else
		new_str = ft_strdup(prefix);
	return (new_str);
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
	prefix = create_prefix_and_cleanup(temp_word, i, var_name);
	if (!prefix)
	{
		free(var_value);
		return (NULL);
	}
	new_str = join_prefix_value(prefix, var_value);
	free(prefix);
	free(var_name);
	if (!new_str)
		return (NULL);
	j = find_var_end(temp_word, i);
	return (finalize_expansion(new_str, temp_word, j));
}

void	update_quote_state(char c, char *quote_type, int *in_quotes)
{
	if ((c == '\'' || c == '"') && (!*in_quotes || c == *quote_type))
	{
		if (*in_quotes == 1)
		{
			*in_quotes = 0;
			*quote_type = 0;
		}
		else
		{
			*in_quotes = 1;
			*quote_type = c;
		}
	}
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*process_dollar_sign(char *current, int i, t_env *envp)
{
	char	*result;

	if (current[i + 1] == '\0' || !is_valid_var_char(current[i + 1]))
		return (current);
	result = replace_variable(current, i, envp);
	return (result);
}
