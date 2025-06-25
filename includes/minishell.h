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
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
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

/* Structures de base définies séparément pour compatibilité C */
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

typedef struct s_command
{
	char		**args;				/* Arguments de la commande (argv) */
	t_token		*redirections;		/* Liste des tokens de redirection */
}	t_command;

typedef struct s_pipeline
{
	t_command	**commands;
	int			cmd_count;
	int			**pipes;
}	t_pipeline;

typedef struct s_parse_context
{
	int		arg_count;				/* Nombre d'arguments */
	int		redirection_count;		/* Nombre de redirections */
	char	**temp_args;			/* Arguments temporaires */
	t_token	*temp_redirections;		/* Redirections temporaires */
}	t_parse_context;

/**
 * Structure unifiée regroupant toutes les données du minishell
 * (sauf t_global qui reste séparée)
 */
typedef struct s_minishell
{
	t_token			*tokens;			/* Liste des tokens */
	t_env			env;				/* Environnement */
	t_command		**commands;			/* Commandes */
	t_pipeline		*pipeline;			/* Pipeline */
	t_parse_context	parse_ctx;			/* Contexte de parsing */
}	t_minishell;

typedef struct s_global
{
	t_env	*env;
	int		shell_status;
	int		exit_status;
	int		signal_received;
	pid_t	child_pid;
}	t_global;

extern t_global	g_global;

typedef struct s_quote_state
{
	int		in_quotes;
	char	quote_type;
}	t_quote_state;

typedef struct s_dollar_context
{
	char	*current;
	int		i;
	char	quote_type;
	t_env	*envp;
}	t_dollar_context;

/* ========================================================================== */
/*                            FONCTIONS LEXER                               */
/* ========================================================================== */

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
char			*extract_and_expand_word(char *input,
					int start, int end, int should_expand);
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
int				handle_redirections(t_token *token, t_env *envp,
					t_token *token_lexer, t_pipeline *pipeline);
int				apply_single_redirection(t_token *token, t_env *env,
					t_token *token_lexer, t_pipeline *pipeline);
int				redirect_output_trunc(char *filename);
int				redirect_output_append(char *filename);
char			*handle_heredoc(char *delimiter,
					int should_expand, t_env *envp);
void			cleanup_heredoc(char *filename);

char			*expand(char *arg, t_env *envp);
char			*expand_once(char *arg, t_env *envp);
char			*expand_variables(char *temp_word, t_env *envp);
char			*process_quotes_and_expand(char *word, t_env *envp);
char			*extract_var_name(char *str);
char			*get_env_value(char *var_name, t_env *envp);
char			*handle_expansion(char *prefix, char *var_value, char *suffix);
char			*remove_quotes(char *str);
char			*finalize_expansion(char *new_str, char *temp_word, int j);
int				find_var_end(char *str, int start);
void			update_quote_state(char c, char *quote_type, int *in_quotes);
int				is_valid_variable(char *str, int i);
char			*process_expansion_loop(char *current,
					t_env *envp, int *found_var);
char			*build_replacement_string(char *prefix, char *var_value);
char			*replace_variable(char *temp_word, int i, t_env *envp);

void			setup_interactive_signals(void);
void			setup_child_signals(void);
void			setup_execution_signals(void);

// Error handling functions
void			print_command_not_found(char *cmd);
void			print_syntax_error(void);
void			print_syntax_error_token(char *token);
int				error_token(t_token *token);
int				check_syntax_errors(t_token *tokens);
int				run_builtin(char **args, t_env *envp);
t_command		*parse_line(char *line);
void			free_tokens(t_token **tokens);
void			restore_file_descriptors(int stdin_backup, int stdout_backup);
int				save_file_descriptors(int *stdin_backup, int *stdout_backup);
void			free_cmd(t_command *cmd);
int				init_command(t_token *token, t_command **cmd);
int				is_redirection(t_token *token);

/* ========================================================================== */
/*                            FONCTIONS BUILT-IN                            */
/* ========================================================================== */

int				count_env(char **env, t_env *envp);
int				echo(char **args);
int				execute_builtin(t_token *token, t_env *envp);
int				exit_shell(char **args);
int				export_var(t_env *envp, char **args);
int				cd(char **args, t_env *envp);
int				pwd(void);
int				print_env(t_env *envp);
int				unset_var(char **args, t_env *envp);
void			sort_env(char **env, int count);
char			**env_cpy(t_env *envp);
int				update_env(t_env *envp, char *arg, char *value);
int				find_env_var_index(char **env, char *arg);
void			print_sorted_env(int count, t_env *envp);
char			*ft_strjoin3(char *s1, char *s2, char *s3);
int				is_valid_identifier(char *str);
int				is_valid_value(char *str);
int				update_env_var(t_env *envp, char *var);
char			*get_var_name(char *str);
char			*get_var_value(char *str);
int				has_plus_equals(char *str);
char			*get_current_value(char **env, char *var_name);
int				has_equals_sign(char *str);
char			*join_if_append(char *value, char *current);
int				update_export_var(t_env *envp, char *var);
int				is_builtin(char *cmd);

/* Utils env functions */
char			*update_shlvl(char **env);
char			**create_default_env(void);
int				init_count(t_env *envp, char **env);
int				init_env_vars(t_env *envp, char **env, int i);
int				init_export_vars(t_env *envp, int i);

/* ========================================================================== */
/*                            FONCTIONS EXEC                                */
/* ========================================================================== */

char			**get_path_cut(t_env *env);
char			*find_path(char *cmd, t_env *env);
void			first_child(t_token *token, t_env *env);
void			free_array(char **array);

/* ========================================================================== */
/*                            FONCTIONS PIPELINE                            */
/* ========================================================================== */

/* pipeline_utils1.c */
void			close_pipes(int **pipes, int cmd_count);
int				**init_pipe_array(int cmd_count);
int				**create_pipes(int cmd_count);
void			setup_pipes(int **pipes, int cmd_index, int cmd_count);

/* pipeline_utils2.c */
t_token			*create_command_token(t_command *cmd);
void			execute_external_command(t_command *cmd,
					t_minishell *minishell, t_token *token);
void			execute_pipeline_command(t_command *cmd,
					int cmd_index, t_minishell *minishell);
void			handle_builtin_execution(t_command *cmd,
					t_minishell *minishell, t_token *token);

/* pipeline_utils3.c */
int				count_commands(t_token *tokens);
int				count_args(t_token *cmd_start);
int				copy_command_args_only(t_command *cmd, t_token *cmd_start);
int				init_command_args(t_command *cmd, t_token *cmd_start,
					int arg_count);

/* create_pipeline.c */
t_command		*init_single_command(t_token *cmd_start);
t_pipeline		*init_pipeline_struct(int cmd_count);
t_pipeline		*create_pipeline(t_token *tokens);

/* pipeline.c */
int				init_pipeline_execution(t_pipeline *pipeline, pid_t **pids);
int				handle_fork_error(t_pipeline *pipeline, pid_t *pids, int i);
int				wait_for_children(t_pipeline *pipeline, pid_t *pids);
int				execute_pipeline(t_pipeline *pipeline,
					t_env *envp, t_token *token_lexer);
void			cleanup_minishell(void);
int				check_syntax_errors(t_token *tokens);
int				check_redirection_error(t_token *current);
int				check_pipe_error(t_token *current);
void			setup_execution_signals(void);
void			sigquit_handler(int sig);
void			sigint_handler(int sig);
void			sigtstp_handler(int sig);
int				is_quoted_delimiter(char *delim);
char			*remove_quotes_from_delimiter(char *delim);
char			*create_heredoc_filename(void);
void			write_heredoc_content(int fd, char *delimiter,
					int should_expand, t_env *envp);
void			restore_fds_and_exit(int *saved_fds, t_minishell *minishell);
void			setup_command_io(t_pipeline *pipeline,
					int cmd_index, int *saved_fds);
void			init_global(t_env *envp);
int				process_line(char *line, t_env *envp);
void			execute_single_command(t_token *tokens, t_env *envp);
int				find_command_token(t_token *tokens);
char			*prompt_and_read(void);
char			*process_dollar_sign(char *current, int i, t_env *envp);
char			*create_prefix_and_cleanup(char *temp_word,
					int i, char *var_name);
char			*expand_loop(char *result, t_env *envp);
#endif