/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:05:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/06 17:07:23 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_execute(t_list *cmd, t_env *env, char **envp)
{
    char *path;
    char **command;
    int i;

    i = 0;
    path = ft_get_path(cmd, env);
    if (!path)
        return (-1);
    command = ft_join_for_execve(cmd);
    if (!command)
        return (-1);
    return (execve(path, command, envp));
}

int ft_pipex(t_data *data, char **envp)
{
    t_list *temp;
    t_list *tmp;
    int total;
    int *tab;

    total = 0;
    tmp = data->cmd;
    while (tmp)
    {
        total++;
        tmp = tmp->nxt;
    }
    // printf("total-->%d\n", total);
    tab = (int *)malloc(sizeof(int) * total);
    int i = 0;

    temp = data->cmd;
    while (temp)
    {
        if (temp->first && temp->last && ft_is_builtin(temp->value))
            return (ft_execute_builtin(temp, data));

        if (!temp->last)
        {
            if (pipe(data->pd) == -1)
                exit(127);
        }
        data->pid = fork();
        if (data->pid == -1)
            return (-1);
        tab[i] = data->pid;
        if (data->pid == 0)
        {
            // Child process
            // printf("infile--> %d\n",temp->infile);
            if (temp->infile != 0)
            {
                if (temp->infile == -1)
                    exit(1);
                // printf("infile--> %d\n", temp->infile);
                if (dup2(temp->infile, 0) == -1)
                    perror("infile");
                close(temp->infile);
            }
            // printf("outfile--> %d\n", temp->outfile);
            if (temp->outfile != 1)
            {
                if (temp->outfile == -1)
                    exit(1);
                if (dup2(temp->outfile, 1) == -1)
                    perror("outfile");
                close(temp->outfile);
            }
            if (!temp->first)
            {
                if (dup2(data->save, temp->infile) == -1)
                    return (-1);
                close(data->save);
            }
            if (!temp->last)
            {
                if (dup2(data->pd[1], temp->outfile) == -1)
                    return (-1);
                close(data->pd[0]);
                close(data->pd[1]);
            }
            if (ft_is_builtin(temp->value))
            {
                ft_execute_builtin(temp, data);
                exit(EXIT_SUCCESS);
            }
            else
            {
                if (ft_execute(temp, data->env, envp) == -1)
                {
                    ft_putstr_fd("command not found: ", 2);
                    ft_putstr_fd(temp->value, 2);
                    ft_putstr_fd("\n", 2);
                }
                exit(EXIT_SUCCESS);
            }
        }
        if (!temp->first)
            close(data->save);
        if (!temp->last)
        {
            close(data->pd[1]);
            data->save = dup(data->pd[0]);
            close(data->pd[0]);
        }
        i++;
        temp = temp->nxt;
    }
    close(data->save);
    i = 0;
    while (i < total)
    {
        // printf("pid-->|%d|\n", tab[i]);
        waitpid(tab[i], NULL, 0);
        i++;
    }
    free(tab);
    if (data && data->fds)
    {
        i = 0;
        while (data->fds[i] > 0)
        {
            // printf("data->fd==%d\n",data->fds[i]);
            close(data->fds[i]);
            i++;
        }
    }

    return (SUCCESS);
}
