/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/26 21:43:48 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_change_pwd(char *buf, t_env **envp, t_data *data)
{
	t_env	*env;

	env = *envp;
	while (env)
	{
		if (ft_strcmp((env)->key, "PWD") == 0)
			(env)->value = gc_strdup(buf, &data->addr_env);
		(env) = (env)->next;
	}
	return (SUCCESS);
}

int	ft_change_oldpwd(char *buf, t_env **envp, t_data *data)
{
	t_env	*env;

	env = *envp;
	while (env)
	{
		if (ft_strcmp((env)->key, "OLDPWD") == 0)
			(env)->value = gc_strdup(buf, &data->addr_env);
		(env) = (env)->next;
	}
	return (SUCCESS);
}

int	ft_home_dir(t_env **envp, t_data *data)
{
	t_env	*env;
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];

	env = *envp;
	while (env)
	{
		if (ft_strcmp((env)->key, "HOME") == 0)
		{
			ft_strlcpy(oldpwd, ft_get_cwd(NULL, 0), PATH_MAX);
			if (chdir((env)->value) == -1)
			{
				perror("cd: ");
				ft_putstr_fd("cd: HOME not set\n", 2);
				return (ERROR);
			}
			ft_strlcpy(pwd, ft_get_cwd(NULL, 0), PATH_MAX);
			ft_change_pwd(pwd, envp, data);
			ft_change_oldpwd(oldpwd, envp, data);
			return (SUCCESS);
		}
		(env) = (env)->next;
	}
	ft_putstr_fd("cd: HOME not set\n", 2);
	return (ERROR);
}

int	ft_cd_with_args(t_list *cmd, t_env **envp, t_data *data)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*ptr;

	ft_strlcpy(oldpwd, ft_get_cwd(NULL, 0), PATH_MAX);
	if (chdir(cmd->args[0]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (ERROR);
	}
	ptr = getcwd(NULL, 0);
	if (!ptr)
	{
		perror("cd: ..");
		ft_get_cwd(cmd->args[0], 1);
	}
	free(ptr);
	ft_strlcpy(pwd, ft_get_cwd(NULL, 0), PATH_MAX);
	ft_change_pwd(pwd, envp, data);
	if (ft_change_oldpwd(oldpwd, envp, data) == 0)
		(data)->oldpwd = 0;
	return (SUCCESS);
}

int	ft_cd(t_list *cmd, t_env **envp, t_data *data)
{
	if (cmd->args)
		return (ft_cd_with_args(cmd, envp, data));
	else
		return (ft_home_dir(envp, data));
	return (SUCCESS);
}
