/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/22 15:42:16 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ] OLDENV
// [ ] update env in the case of inset 


int ft_env(char **envp)
{
    (void)envp;
    return 1;
}

void ft_fill_env(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        if (ft_strcmp(env->key, "PATH") == 0)
        {
            env->env = ft_strdup(env->value);
        }
        env = env->next;
    }
}

int main(int argc, char *argv[], char *env[])
{
    ft_env(env);
    return 0;
}
