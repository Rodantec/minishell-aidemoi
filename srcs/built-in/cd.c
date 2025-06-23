/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:56:17 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/28 10:56:17 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"
#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	update_pwd_vars(t_env *envp, char *oldpwd, char *pwd)
{
	char	*oldpwd_var;
	char	*pwd_var;
	int		status;

	oldpwd_var = ft_strjoin3("OLDPWD", "=", oldpwd);
	pwd_var = ft_strjoin3("PWD", "=", pwd);
	if (!oldpwd_var || !pwd_var)
	{
		free(oldpwd_var);
		free(pwd_var);
		return (1);
	}
	status = update_env_var(envp, oldpwd_var)
		|| update_env_var(envp, pwd_var)
		|| update_export_var(envp, oldpwd_var)
		|| update_export_var(envp, pwd_var);
	free(oldpwd_var);
	free(pwd_var);
	return (status);
}

int	cd(char **args, t_env *envp)
{
	char	*oldpwd;
	char	*pwd;
	int		arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (!args[1] || ft_strcmp(args[1], "--") == 0)
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror("cd"), free(oldpwd), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (chdir(getenv("OLDPWD")) != 0)
			return (perror("cd"), free(oldpwd), 1);
	}
	else if (chdir(args[1]) != 0)
		return (perror("cd"), free(oldpwd), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), 1);
	update_pwd_vars(envp, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}
