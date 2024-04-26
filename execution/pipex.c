/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:05:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/25 18:25:42 by oumimoun         ###   ########.fr       */
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
    ft_putstr_fd("command not found: ", 2);
    ft_putstr_fd(cmd->value, 2);

    return (0);
}

int ft_pipex(t_data *data, t_env *env)
{
    t_list *temp;

    temp = data->cmd;
    temp = temp->nxt;
    while (temp->nxt)
    {
        printf("value-->%s\n", temp->value);
        if (pipe(data->pd) == -1)
            return (-1);
        data->pid = fork();
        printf("data->pid-->%d\n",data->pid);
        if (data->pid == -1)
            return (-1);
        if (data->pid == 0)
        {
            // child

            close(data->pd[0]);
            if (dup2(temp->infile, 0) == -1)
                return (-1);
            close(temp->infile);
            if (data->save != -1 && dup2(data->save, 0) == -1)
                return (-1);
            close(data->save);
            // last cmd
            printf("here on the child\n");
            if (dup2(data->pd[1], temp->outfile) == -1)
                return (-1);
            close(data->pd[1]);
            // mataywselch hna
            ft_execute(temp, env);
        }
        close(data->save);
        data->save = dup(data->pd[0]);
        if (data->save == -1)
            return (-1);
        close(data->pd[0]);
        close(data->pd[1]);
        temp = temp->nxt;
    }
    close(data->save);
    // printf("value-->%s\n", temp->value);
    // ft_execute(temp, env);
    while (waitpid(-1, NULL, 0) != -1)
        ;
    return (0);
}


