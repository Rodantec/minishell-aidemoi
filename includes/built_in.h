/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:42:44 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 10:42:44 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../libft/libft.h"
# include "exec.h"
# include "minishell.h"

int		count_env(char **env, t_env *envp);
int		echo(char **args);
int		execute_builtin(t_token *token, t_env *envp);
int		exit_shell(char **args);
int		export_var(t_env *envp, char **args);
int		cd(char **args, t_env *envp);
int		pwd(void);
int		print_env(t_env *envp);
int		unset_var(char **args, t_env *envp);
void	sort_env(char **env, int count);
char	**env_cpy(t_env *envp);
int		update_env(t_env *envp, char *arg, char *value);
int		find_env_var_index(char **env, char *arg);
void	print_sorted_env(int count, t_env *envp);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		is_valid_identifier(char *str);
int		is_valid_value(char *str);
int		update_env_var(t_env *envp, char *var);
char	*get_var_name(char *str);
char	*get_var_value(char *str);
int		has_plus_equals(char *str);
char	*get_current_value(char **env, char *var_name);
int		has_equals_sign(char *str);
int		update_export_var(t_env *envp, char *var);
int     is_builtin(char *cmd);

/* Utils env functions */
char	*update_shlvl(char **env);
char	**create_default_env(void);
int		init_count(t_env *envp, char **env);
int		init_env_vars(t_env *envp, char **env, int i);
int		init_export_vars(t_env *envp, int i);

#endif
