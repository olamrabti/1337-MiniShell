/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/30 17:39:11 by oumimoun         ###   ########.fr       */
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

int ft_cd(t_list *cmd, t_env *envp)
{
    t_env *env;

    env = envp;
    if (cmd->args)
    {
        if (chdir(cmd->args[0]) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": no such file or directory\n", 2);
            return (ERROR);
        }
    }
    else
    {
        while (env)
        {
            if (ft_strncmp(env->key, "HOME", 4) == 0)
            {
                if (chdir(env->value) == -1)
                {
                    ft_putstr_fd("cd: HOME not set\n", 2);
                    return (ERROR);
                }
            }
            env = env->next;
        }
    }

    return (SUCCESS);
}
