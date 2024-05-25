/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:36:50 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/25 15:25:52 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

char **ft_get_paths(t_env *env, t_data *data)
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
            path = ft_split(temp->value, ':', data);
            return (path);
        }
        temp = temp->next;
    }
    return (NULL);
}

void ft_print_error_path(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": No such file or director", 2);
}

char *ft_get_path(t_list *cmd, t_env *env, t_data *data)
{
    char **paths;
    char *full_path;
    int i;

    i = -1;
    if (access(cmd->value, X_OK) == 0)
        return (gc_strdup(cmd->value, &data->addr));
    if (ft_strncmp(cmd->value, "/", 1) == 0)
    {
        if (access(cmd->value, X_OK) == 0)
            return (gc_strdup(cmd->value, &data->addr));
        else
            ft_print_error_path(cmd->value);
    }
    paths = ft_get_paths(env, data);
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

int count_args(char **args)
{
    int total = 0;
    while (args && args[total])
        total++;
    return total;
}

char **allocate_command_array(t_addr *addr, int total)
{
    return ft_calloc(&addr, total + 2, sizeof(char *));
}

void copy_command_value(char **command, t_list *cmd, t_addr *addr)
{
    command[0] = gc_strdup(cmd->value, &addr);
}

void copy_command_args(char **command, t_list *cmd, t_addr *addr)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (cmd->args && cmd->args[j])
    {
        command[i] = gc_strdup(cmd->args[j], &addr);
        i++;
        j++;
    }
    command[i] = NULL;
}

char **ft_join_for_execve(t_list *cmd, t_addr *addr)
{
    int total;
    char **command;

    total = count_args(cmd->args);
    command = allocate_command_array(addr, total);
    copy_command_value(command, cmd, addr);
    copy_command_args(command, cmd, addr);
    return command;
}
