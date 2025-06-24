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

static int	change_directory(char *target_dir)
{
	if (!target_dir || ft_strcmp(target_dir, "--") == 0)
		return (chdir(getenv("HOME")));
	else if (ft_strcmp(target_dir, "-") == 0)
		return (chdir(getenv("OLDPWD")));
	else
		return (chdir(target_dir));
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
		return (ft_putendl_fd("minishell: cd: too many arguments",
				STDERR_FILENO), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (change_directory(args[1]) != 0)
		return (perror("cd"), free(oldpwd), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), 1);
	update_pwd_vars(envp, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}
