/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:36:50 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/23 15:27:33 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_is_one_cmd(t_data *data)
{
    t_list *temp;

    temp = data->cmd->nxt;
    if (temp && temp->value && temp->nxt)
        return 0;
    return 1;
}

char *ft_get_path(t_list *cmd, t_env *env)
{
    char *full_path;
    int i;

    i = -1;
    if (access(cmd->value, X_OK | R_OK | F_OK) == 0)
        return (ft_strdup(cmd->value));
    if (ft_strncmp(cmd->value, "/", 1) == 0)
    {
        if (access(cmd->value, X_OK | R_OK | F_OK) == 0)
            return (ft_strdup(cmd->value));
        else
        {
            ft_putstr_fd(cmd->value, 2);
            ft_putstr_fd(": No such file or director", 2);
        }
    }
    while (env->path && env->path[++i])
    {
        full_path = ft_strjoin(env->path[i], "/");
        full_path = ft_strjoin(full_path, cmd->value);
        if (access(full_path, X_OK | R_OK | F_OK) == 0)
            return (full_path);
        free(full_path);
        full_path = NULL;
    }
    return (NULL);
}


char **ft_join_for_execve(t_list *cmd)
{
    char **command;
    char **split;
    int total;
    int i;
    int j;
    
    total = 0;
    while (cmd->args[total])
        total++;
    command = (char **)malloc(sizeof(char *) * total + 1);
    if (!command)
        return (NULL);
    command[0] = ft_strdup(cmd->value);
    command[0] = strdup(cmd->value);
    if (!command[0])
    {
        free(command);
        return (NULL);
    }
    i = 1;
    j = 0;
    while (cmd->args[j])
    {
        command[i] = ft_strdup(cmd->args[j]);
        if (!command[i])
        {
            while (i >= 0)
            {
                free(command[i]);
                i--;
            }
            free(command);
            return (NULL);
        }
        i++;
        j++;
    }
}

// [ ] todo redir to outfile befor exeve() so i gotta fok() even its one cmd

int execute_one_command(t_list *cmd, t_env *env)
{
    char *path;
    char **command;

    if (dup2(cmd->infile, 0) == -1)
        return (-1);
    path = ft_get_path(cmd, env);
    if (!path)
        return (-1);
    command = ft_join_for_execve(cmd);
    if (!command)
        return (-1);
    execve(path, command, NULL);
    ft_putstr_fd("command not found: ", 2);
    ft_putstr_fd(cmd->value, 2);
    dup2(cmd->outfile, 1);
    return (0);
}
