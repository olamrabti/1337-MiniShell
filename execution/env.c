/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/18 11:02:51 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_env(t_list *cmd, t_env **envp, t_data *data)
{
    t_env *env;

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
        if (env && env->key && env->value)
        {
            if (data->is_hiden == 1 && strcmp(env->key, "PATH") == 0)
            {
                env = env->next;
                continue;
            }
            if (data->oldpwd == 1 && strcmp(env->key, "OLDPWD") == 0)
            {
                env = env->next;
                continue;
            }
            printf("%s=%s\n", env->key, env->value);
        }
        env = env->next;
    }
    return (SUCCESS);
}
