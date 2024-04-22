/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:02 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/22 12:00:55 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// [ ]: start the execution of the commands


int ft_is_one_cmd(t_data *data)
{
    t_data *temp;

    temp = data;
    if (temp->next == NULL)
        return (1);
    return (0);
}

int ft_is_builtin(t_data *data)
{
    if (ft_strncmp(data->cmd, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(data->cmd, "cd", 2) == 0)
        return (1);
    if (ft_strncmp(data->cmd, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(data->cmd, "export", 6) == 0)
        return (1);
    if (ft_strncmp(data->cmd, "unset", 5) == 0)
        return (1);
    if (ft_strncmp(data->cmd, "env", 3) == 0)
        return (1);
    if (ft_strncmp(data->cmd, "exit", 4) == 0)
        return (1);
    return (0);
}


void execute_commands(t_data *data, char **envp, int status)
{
    t_data *temp;
    t_env env;

    // env = ft_env(envp);

    temp = data;
    if (ft_is_one_cmd(temp))
    {
        if (ft_is_builtin(temp))
            execute_builtin(data->cmd, env);
        else
            execute_command(data->cmd, env);
    }
    else
    {
        while (data)
        {
            if (ft_is_builtin(data->cmd))
                execute_builtin(data->cmd, env);
            else
                execute_command(data->cmd, env);
            data = data->next;
        }
    }
}
