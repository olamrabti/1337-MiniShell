/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/06 11:47:43 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ] OLDENV
// [ ] update env in the case of inset

int ft_env(t_list *cmd, t_env **envp)
{
    t_env *env;

    printf("[%p] hadi wst env \n", *envp);
    env = *envp;
    if (cmd->args != NULL)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (ERROR);
    }
    while (env)
    {
        if ( env && env->key && env->value)
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
    return (SUCCESS);
}
