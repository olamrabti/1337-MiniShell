/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/24 15:09:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_change_pwd(char *buf, t_env **envp, t_data *data)
{
    t_env *env;

    env = *envp;
    while (env)
    {
        if (ft_strcmp((env)->key, "PWD") == 0)
            (env)->value = gc_strdup(buf, &data->addr);
        (env) = (env)->next;
    }

    return (SUCCESS);
}

int ft_change_oldpwd(char *buf, t_env **envp, t_data *data)
{
    t_env *env;

    env = *envp;
    while (env)
    {
        if (ft_strcmp((env)->key, "OLDPWD") == 0)
            (env)->value = gc_strdup(buf, &data->addr);
        (env) = (env)->next;
    }
    return (SUCCESS);
}

int ft_cd(t_list *cmd, t_env **envp, t_data *data)
{
    t_env *env;
    char oldpwd[PATH_MAX];
    char pwd[PATH_MAX];

    env = *envp;
    if (cmd->args)
    {
        ft_strlcpy(oldpwd, ft_get_cwd(NULL, 0), PATH_MAX);
        if (chdir(cmd->args[0]) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": no such file or directory\n", 2);
            return (ERROR);
        }
        if (!getcwd(NULL, PATH_MAX))
        {
            perror("cd: ..");
            ft_get_cwd(cmd->args[0], 1);
        }
        ft_strlcpy(pwd, ft_get_cwd(NULL, 0), PATH_MAX);
        ft_change_pwd(pwd, envp, data);
        if (ft_change_oldpwd(oldpwd, envp, data) == 0)
            (data)->oldpwd = 0;
    }
    else
    {
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
            }
            (env) = (env)->next;
        }
    }
    return (SUCCESS);
}
