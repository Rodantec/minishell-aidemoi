/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:14:28 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:07 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"
#include "../../includes/built_in.h"

char	**get_path_cut(t_env *env)
{
	int		i;
	char	**pathcut;

	i = 0;
	while (env->env[i] && ft_strnstr(env->env[i], "PATH=", 5) == NULL)
		i++;
	if (!env->env[i])
		return (NULL);
	pathcut = ft_split(env->env[i] + 5, ':');
	return (pathcut);
}

char	*try_paths(char **pathcut, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			return (NULL);
		}
		return (NULL);
	}
	while (pathcut[i])
	{
		temp = ft_strjoin(pathcut[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	**pathcut;
	char	*path;

	pathcut = get_path_cut(env);
	if (!pathcut)
		return (NULL);
	path = try_paths(pathcut, cmd);
	free_array(pathcut);
	return (path);
}

void	run_execve(char *path, char **args, t_env *env)
{
	struct stat	path_stat;
	char		*shlvl;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", args[0]);
		free_array(args);
		free(path);
		exit(126);
	}
	execve(path, args, env->env);
	perror("minishell");
	if (ft_strcmp(args[0], "./minishell") == 0)
	{
		shlvl = update_shlvl(env->env);
		if (shlvl)
		{
			update_env_var(env, shlvl);
			free(shlvl);
		}
	}
	execve(path, args, env->env);
	free_array(args);
	free(path);
	exit(126);
}

void	execute_cmd(t_token *token, t_env *env)
{
	char	**args;
	char	*path;

	args = tokens_to_args(token);
	if (!args || !args[0])
		exit(1);
	path = find_path(args[0], env);
	if (!path)
	{
		if (ft_strchr(args[0], '/'))
		{
			fprintf(stderr, "minishell: %s: No such file or directory\n", args[0]);
			g_global.exit_status = 127;
		}
		else
			print_command_not_found(args[0]);
		free_array(args);
		exit(127);
	}
	run_execve(path, args, env);
}
