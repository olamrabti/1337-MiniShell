/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/05 17:37:59 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ] OLDENV
// [ ] update env in the case of inset 


// int ft_env(t_list * cmd, t_env **envp)
// {
//     t_env *env;

//     env = *envp;
//     if (cmd->args != NULL)
//     {
//         ft_putstr_fd("env: ", 2);
//         ft_putstr_fd(cmd->args[0], 2);
//         ft_putstr_fd(": No such file or directory\n", 2);
//         return (ERROR);
//     }
//     while (env)
//     {
//         if (!env->value )
//             env = env->next;
//         else
//         {
//             printf("%s=%s\n", env->key, env->value);
//             env = env->next;
//         }
        
//     }
//     return (SUCCESS);
// }


int ft_env(t_list *cmd, t_env **envp)
{
    t_env *env;

    env = *envp;
    if (!env)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (ERROR);
    }
    t_env *tmp=*envp;
    while (tmp)
    {
        if (tmp && !tmp->value)
        {
            tmp = tmp->next;
        }
        else
        {
            if(tmp)
                printf("%s=%s\n", tmp->key, tmp->value);
            tmp = tmp->next;
        }
    }
    return (SUCCESS);
}
