/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 11:10:41 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "minishell.h"

/* expand.c */
char		*expand(char *arg, t_env *envp);

/* pipeline_utils1.c */
void		close_pipes(int **pipes, int cmd_count);
int			**init_pipe_array(int cmd_count);
int			**create_pipes(int cmd_count);
void		setup_pipes(int **pipes, int cmd_index, int cmd_count);

/* pipeline_utils2.c */
t_token		*create_command_token(t_command *cmd);
void		execute_external_command(t_command *cmd,
				t_env *envp, t_token *token, t_pipeline *pipeline, t_token *token_lexer);
void		execute_pipeline_command(t_command *cmd, int cmd_index,
				t_pipeline *pipeline, t_env *envp, t_token *token_lexer);

/* pipeline_utils3.c */
int			count_commands(t_token *tokens);
int			count_args(t_token *cmd_start);
int			copy_command_args_only(t_command *cmd, t_token *cmd_start);
int			init_command_args(t_command *cmd, t_token *cmd_start,
				int arg_count);

/* create_pipeline.c */
t_command	*init_single_command(t_token *cmd_start);
t_pipeline	*init_pipeline_struct(int cmd_count);
t_pipeline	*create_pipeline(t_token *tokens);

/* pipeline.c */
int			init_pipeline_execution(t_pipeline *pipeline, pid_t **pids);
int			handle_fork_error(t_pipeline *pipeline, pid_t *pids, int i);
int			wait_for_children(t_pipeline *pipeline, pid_t *pids);
int			execute_pipeline(t_pipeline *pipeline, t_env *envp, t_token *token_lexer);

#endif 