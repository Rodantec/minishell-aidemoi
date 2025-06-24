/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:33:57 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 18:33:57 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*create_prefix_and_cleanup(char *temp_word, int i, char *var_name)
{
	char	*prefix;

	prefix = ft_substr(temp_word, 0, i);
	if (!prefix)
		free(var_name);
	return (prefix);
}

char	*expand_loop(char *result, t_env *envp)
{
	char	*temp;
	char	*old_result;

	while (ft_strchr(result, '$'))
	{
		old_result = result;
		temp = expand_once(result, envp);
		if (!temp || ft_strcmp(result, temp) == 0)
		{
			free(temp);
			break ;
		}
		result = temp;
		free(old_result);
	}
	return (result);
}
