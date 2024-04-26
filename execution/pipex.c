/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:05:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/26 15:25:15 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_execute(t_list *cmd, t_env *env)
{
    char *path;
    char **command;

    path = ft_get_path(cmd, env);
    if (!path)
        return (-1);
    command = ft_join_for_execve(cmd);
    if (!command)
        return (-1);
    execve(path, command, NULL);
    perror("command not found: ");
    // ft_putstr_fd("command not found: ", 2);
    // ft_putstr_fd(cmd->value, 2);
    exit(127);

    return (0);
}

int ft_pipex(t_data *data, t_env *env)
{
    t_list *temp;

    temp = data->cmd;
    while (temp)
    {
        if (temp->first && temp->last)
        {
            data->pid = fork();
            if (data->pid == 0)
            {
                ft_execute(temp, env);
                return (0);
            }
            else
            {
                waitpid(-1, NULL, 0);
                return (0);
            }
            
        }
        if (!temp->last)
        {
            if (pipe(data->pd) == -1)
                return (-1);
        }
        data->pid = fork();
        if (data->pid == -1)
            return (-1);
        if (data->pid == 0)
        {
            // child
            if (!temp->first)
            {
                if (dup2(data->save, STDIN_FILENO) == -1)
                    return (-1);
                close(data->save);
            }
            if (!temp->last)
            {
                if (dup2(data->pd[1], STDOUT_FILENO) == -1)
                    return (-1);
                close(data->pd[1]);
                close(data->pd[0]);
            }
            ft_execute(temp, env);

            // if (dup2(data->pd[1], temp->outfile) == -1)
            //     return (-1);
            // close(data->pd[1]);
            // // mataywselch hna
            // ft_execute(temp, env);
        }
        if (!temp->first)
        {
            close(data->save);
        }
        if (!temp->last)
        {
            close(data->pd[1]);
            data->save = dup(data->pd[0]);
        }

        // close(data->save);
        // data->save = dup(data->pd[0]);
        // if (data->save == -1)
        //     return (-1);
        // close(data->pd[0]);
        // close(data->pd[1]);
        temp = temp->nxt;
    }
    // close(data->save);
    // printf("value-->%s\n", temp->value);
    // ft_execute(temp, env);
    while (waitpid(-1, NULL, 0) != -1)
        ;
    return (0);
}
