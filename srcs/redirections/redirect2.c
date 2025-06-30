/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:52:36 by lkiloul           #+#    #+#             */
/*   Updated: 2025/06/24 16:52:36 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_redirect(t_token *token)
{
	char	*clean;
	char	*filename;
	int		expand;
	int		result;

	expand = !is_quoted_delimiter(token->next->value);
	clean = remove_quotes_from_delimiter(token->next->value);
	filename = handle_heredoc(clean, expand, g_global.env);
	free(clean);
	if (!filename)
		return (-1);
	result = redirect_input(filename);
	cleanup_heredoc(filename);
	return (result);
}

int	apply_single_redirection(t_token *token, t_env *env,
	t_token *token_lexer, t_pipeline *pipeline)
{
	(void)pipeline;
	if (!token || !token->next || token->next->type != TOKEN_WORD)
		return (-1);
	if (token->type == TOKEN_REDIR_OUT)
		return (redirect_output_trunc(token->next->value));
	if (token->type == TOKEN_APPEND)
		return (redirect_output_append(token->next->value));
	if (token->type == TOKEN_REDIR_IN)
	{
		if (redirect_input(token->next->value) < 0)
		{
			if(token_lexer)
				free_tokens(&token_lexer);
			if(env)
				free_env(env);
			if(pipeline)
				free_pipeline(pipeline);
			return -1;
		}
		return (0);
	}
	if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc_redirect(token));
	return (0);
}

t_token	*extract_redirections(t_token *tokens)
{
	t_token	*head;
	t_token	*cur;
	t_token	*redir;
	t_token	*file;

	head = NULL;
	cur = tokens;
	while (cur)
	{
		if (is_redirection(cur) && cur->next && cur->next->type == TOKEN_WORD)
		{
			redir = create_token(cur->type, cur->value);
			file = create_token(cur->next->type, cur->next->value);
			if (!redir || !file)
				return (NULL);
			redir->next = file;
			head = redir;
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (head);
}
