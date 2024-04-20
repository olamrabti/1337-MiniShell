/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:02 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/20 12:04:39 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// [ ]: start the execution of the commands

int ft_is_one_cmd(t_list *list)
{
    t_list *temp;

    temp = list;
    if (temp->next == NULL)
        return (1);
    return (0);
}

int ft_is_builtin(t_list *list)
{
    if (ft_strncmp(list->cmd, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(list->cmd, "cd", 2) == 0)
        return (1);
    if (ft_strncmp(list->cmd, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(list->cmd, "export", 6) == 0)
        return (1);
    if (ft_strncmp(list->cmd, "unset", 5) == 0)
        return (1);
    if (ft_strncmp(list->cmd, "env", 3) == 0)
        return (1);
    if (ft_strncmp(list->cmd, "exit", 4) == 0)
        return (1);
    return (0);
}


void execute_commands(t_list *list, char **envp)
{
    t_list *temp;
    t_env env;

    env = ft_env(envp);

    temp = list;
    if (ft_is_one_cmd(temp))
    {
        if (ft_is_builtin(temp))
            execute_builtin(list->cmd, env);
        else
            execute_command(list->cmd, env);
    }
    else
    {
        while (list)
        {
            if (ft_is_builtin(list->cmd))
                execute_builtin(list->cmd, env);
            else
                execute_command(list->cmd, env);
            list = list->next;
        }
    }
}
