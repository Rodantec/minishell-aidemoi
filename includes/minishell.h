/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/05/28 11:26:56 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:26:56 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parser.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	int		count_env;
	int		count_export;
	char	**env;
	char	*oldpwd;
	char	**export;
}	t_env;

typedef struct s_global
{
	t_env	*env;
	int		shell_status;
	int		exit_status;
	int		signal_received;
	pid_t	child_pid;
}	t_global;

typedef struct s_pipeline
{
	t_command	**commands;
	int			cmd_count;
	int			**pipes;
}	t_pipeline;

extern t_global	g_global;

t_token			*lexer(char *input);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token **tokens);
void			print_token(t_token *token);
void			print_tokens(t_token *tokens);
int				count_tokens(t_token *tokens);
void			handle_quotes(char c, int *in_quotes, char *quote_type);
int				check_word_end(char *input, int i, int in_quotes);
int				process_special_redirections(char *input, int *i,
					t_token **tokens);
int				is_separator(char c);
t_token_type	get_token_type(char c);
int				process_word(char *input, int *i, t_token **tokens);
int				process_redirection(char *input, int *i, t_token **tokens);
int				process_pipe(char *input, int *i, t_token **tokens);

int				init_env(t_env *envp, char **env);
void			free_env(t_env *envp);

char			**tokens_to_args(t_token *token);
void			execute_cmd(t_token *token, t_env *env);

int				redirect_input(char *filename);

/* free_all.c */
void			free_pipeline(t_pipeline *pipeline);
void			free_token_list(t_token *tokens);
void			cleanup_minishell(void);
int				contains_redirection(t_token *tokens);
int				handle_redirections(t_token *token);
int				redirect_output_trunc(char *filename);
int				redirect_output_append(char *filename);
char			*handle_heredoc(char *delimiter,
					int should_expand, t_env *envp);
void			cleanup_heredoc(char *filename);

char			*expand(char *arg, t_env *envp);
char			*expand_variables(char *temp_word, t_env *envp);
char			*process_quotes_and_expand(char *word, t_env *envp);
char			*extract_var_name(char *str);
char			*get_env_value(char *var_name, t_env *envp);

void			setup_interactive_signals(void);
void			setup_child_signals(void);
void			setup_execution_signals(void);

// Error handling functions
void			print_command_not_found(char *cmd);
void			print_syntax_error(void);
void			print_syntax_error_token(char *token);
int				check_syntax_errors(t_token *tokens);
int				run_builtin(char **args, t_env *envp);
t_command		*parse_line(char *line);
void			free_tokens(t_token **tokens);
int				apply_single_redirection(t_token *token);
void			restore_file_descriptors(int stdin_backup, int stdout_backup);
int				save_file_descriptors(int *stdin_backup, int *stdout_backup);
void	free_cmd(t_command *cmd);
#endif