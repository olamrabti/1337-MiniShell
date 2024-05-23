/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:36:50 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/22 19:33:57 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

char **ft_get_paths(t_env *env)
{
    t_env *temp;
    char **path;

    if (!env)
        return (NULL);
    path = NULL;
    temp = env;
    while (temp)
    {
        if (ft_strncmp(temp->key, "PATH", 4) == 0)
        {
            path = ft_split(temp->value, ':');
            return (path);
        }
        temp = temp->next;
    }
    return (NULL);
}

char *ft_get_path(t_list *cmd, t_env *env)
{
    char **paths;
    char *full_path;
    int i;

    i = -1;
    if (access(cmd->value, X_OK) == 0)
        return (ft_strdup(cmd->value));
    if (ft_strncmp(cmd->value, "/", 1) == 0)
    {
        if (access(cmd->value, X_OK) == 0)
            return (ft_strdup(cmd->value));
        else
        {
            ft_putstr_fd(cmd->value, 2);
            ft_putstr_fd(": No such file or director", 2);
        }
    }
    paths = ft_get_paths(env);
    while (paths && paths[++i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd->value);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        full_path = NULL;
    }
    return (NULL);
}


char **ft_join_for_execve(t_list *cmd, t_addr *addr)
{
    char **command;
    int total;
    int i;
    int j;

    total = 0;
    if (cmd->args)
    {
        while (cmd->args[total])
            total++;
    }
    command = ft_calloc(&addr, (total + 2) , sizeof(char *));
    command[0] = gc_strdup(cmd->value, &addr);
    i = 1;
    j = 0;
    if (cmd->args)
    {
        while (cmd->args[j])
        {
            command[i] = gc_strdup(cmd->args[j], &addr);
            i++;
            j++;
        }
    }
    command[i] = NULL;
    return (command);
}
