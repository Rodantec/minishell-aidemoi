/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:46:39 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 12:57:38 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_token(t_token *token)
{
	while (token)
	{
		if (is_redirection(token)
			&& (!token->next || token->next->type != TOKEN_WORD))
		{
			if (token->next)
				print_syntax_error_token(token->next->value);
			else
				print_syntax_error_token(NULL);
			return (-1);
		}
		token = token->next;
	}
	return (0);
}

int	save_file_descriptors(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	if (*in == -1)
	{
		perror("dup stdin");
		return (-1);
	}
	*out = dup(STDOUT_FILENO);
	if (*out == -1)
	{
		perror("dup stdout");
		close(*in);
		return (-1);
	}
	return (0);
}

void	restore_file_descriptors(int in, int out)
{
	if (in != -1)
	{
		if (dup2(in, STDIN_FILENO) == -1)
			perror("restore stdin");
		close(in);
	}
	if (out != -1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			perror("restore stdout");
		close(out);
	}
}

int	is_quoted_delimiter(char *delim)
{
	int	len;

	if (!delim)
		return (0);
	len = ft_strlen(delim);
	if (len >= 2)
	{
		if ((delim[0] == '\'' && delim[len - 1] == '\'')
			|| (delim[0] == '"' && delim[len - 1] == '"'))
			return (1);
	}
	return (0);
}

char	*remove_quotes_from_delimiter(char *delim)
{
	int		len;

	if (!is_quoted_delimiter(delim))
		return (ft_strdup(delim));
	len = ft_strlen(delim);
	return (ft_substr(delim, 1, len - 2));
}

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

int	apply_single_redirection(t_token *token, t_env *env, t_token *token_lexer, t_pipeline *pipeline)
{
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
			ft_putstr_fd("No such file or directory: ", STDERR_FILENO);
			ft_putendl_fd(token->next->value, STDERR_FILENO);
			free_tokens(&token);
			free_tokens(&token_lexer);
			free_env(env);
			free_pipeline(pipeline);
			return (-1);
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
