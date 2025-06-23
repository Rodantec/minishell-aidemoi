/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:15:00 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 14:15:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(t_token *token)
{
	return (token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_HEREDOC);
}

int	count_words(t_token *tokens)
{
	t_token	*current;
	int		count;

	count = 0;
	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (is_redirection(current))
			current = current->next;
		current = current->next;
	}
	return (count);
}

void	free_args_on_error(char **args, int i)
{
	while (--i >= 0)
		free(args[i]);
	free(args);
}

int	fill_args(t_token *tokens, char **args)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
		{
			args[i] = ft_strdup(current->value);
			if (!args[i])
			{
				free_args_on_error(args, i);
				return (-1);
			}
			i++;
		}
		else if (is_redirection(current))
			current = current->next;
		current = current->next;
	}
	args[i] = NULL;
	return (0);
}

char	**tokens_to_args(t_token *tokens)
{
	int		word_count;
	char	**args;

	word_count = count_words(tokens);
	args = malloc(sizeof(char *) * (word_count + 1));
	if (!args)
		return (NULL);
	if (fill_args(tokens, args) == -1)
	{
		free(args);
		return (NULL);
	}
	return (args);
}

t_command	*parse_line(char *line)
{
	t_command	*cmd;
	t_token		*tokens;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		free_tokens(&tokens);
		return (NULL);
	}
	cmd->args = tokens_to_args(tokens);
	free_tokens(&tokens);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
