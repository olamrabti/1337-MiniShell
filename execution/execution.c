/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:02 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/26 15:43:21 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ]: start the execution of the commands


// int ft_is_builtin(char *value)
// {
//     if (ft_strncmp(value, "echo", 4) == 0)
//         return (1);
//     if (ft_strncmp(value, "cd", 2) == 0)
//         return (1);
//     if (ft_strncmp(value, "pwd", 3) == 0)
//         return (1);
//     if (ft_strncmp(value, "export", 6) == 0)
//         return (1);
//     if (ft_strncmp(value, "unset", 5) == 0)
//         return (1);
//     if (ft_strncmp(value, "env", 3) == 0)
//         return (1);
//     if (ft_strncmp(value, "exit", 4) == 0)
//         return (1);
//     return (0);
// }


int execute_commands(t_data **data, char **envp)
{
    t_env *env;
    // t_list *temp;

    if (!data || !envp)
        return (-1);
    env = ft_parce_env(envp);

    // ft_init_cmds((*data));
    ft_pipex((*data), env);
    return (0);
}
