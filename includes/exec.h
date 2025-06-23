/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:42:47 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 10:42:47 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	*find_path(char *cmd, t_env *env);
char	**tokens_to_args(t_token *token);
void	first_child(t_token *token, t_env *env);
void	free_array(char **array);

#endif