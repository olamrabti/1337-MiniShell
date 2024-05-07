/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/07 17:48:57 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// TODO creating cd
// TODO testing cd
//  [x] cd with no argument
// [ ] cd -
// [ ] cd ~
// [ ] cd chenge oldpwd and pwd

// getcwd geting PWD
// getcwd();

int ft_change_pwd(char *buf, t_env *envp)
{
    t_env *env;

    env = envp;
    while (env)
    {
        if (ft_strcmp(env->key, "PWD") == 0)
        {
            env->value = ft_strdup(buf);
        }
        env = env->next;
    }
    return (SUCCESS);
}

int ft_change_oldpwd(char *buf, t_env *envp)
{
    t_env *env;

    env = envp;
    while (env)
    {
        if (ft_strcmp(env->key, "OLDPWD") == 0)
        {
            env->value = ft_strdup(buf);
        }
        env = env->next;
    }
    return (SUCCESS);
}

int ft_cd(t_list *cmd, t_env *envp)
{
    t_env *env;
    char *oldpwd;
    char *pwd;

    env = envp;
    if (cmd->args)
    {
        oldpwd = getcwd(NULL, 0);
        if (oldpwd == NULL)
        {
            perror("pwd");
            return (ERROR);
        }
        if (chdir(cmd->args[0]) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": no such file or directory\n", 2);
            return (ERROR);
        }
        pwd = getcwd(NULL, 0);
        if (pwd == NULL)
        {
            perror("pwd");
            return (ERROR);
        }
        ft_change_pwd(pwd, envp);
        ft_change_oldpwd(oldpwd, envp);
    }
    else
    {
        while (env)
        {
            if (ft_strcmp(env->key, "HOME") == 0)
            {
                oldpwd = getcwd(NULL, 0);
                if (oldpwd == NULL)
                {
                    perror("pwd");
                    return (ERROR);
                }
                if (chdir(env->value) == -1)
                {
                    ft_putstr_fd("cd: HOME not set\n", 2);
                    return (ERROR);
                }
                pwd = getcwd(NULL, 0);
                if (pwd == NULL)
                {
                    perror("pwd");
                    return (ERROR);
                }
                ft_change_pwd(pwd, envp);
                ft_change_oldpwd(oldpwd, envp);
            }
            env = env->next;
        }
    }

    return (SUCCESS);
}
