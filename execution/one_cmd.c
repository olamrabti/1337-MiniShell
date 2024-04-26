/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:36:50 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/25 17:31:32 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

char	**ft_get_paths(t_env *env)
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
    paths = ft_get_paths(env);
    // printf("path --> %s", paths[0]);
    while (paths && paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd->value);
		if (access(full_path, F_OK | R_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
	}
    return (NULL);
}


// char **ft_join_for_execve(t_list *cmd)
// {
//     char **command;
//     int total;
//     int i;
//     int j;
    
//     total = 0;
//     while (cmd->args[total])
//         total++;
//     command = (char **)malloc(sizeof(char *) * total + 1);
//     if (!command)
//         return (NULL);
//     command[0] = ft_strdup(cmd->value);
//     if (!command[0])
//     {
//         free(command);
//         return (NULL);
//     }
//     i = 1;
//     j = 0;
//     while (cmd->args[j])
//     {
//         command[i] = ft_strdup(cmd->args[j]);
//         if (!command[i])
//         {
//             while (i >= 0)
//             {
//                 free(command[i]);
//                 i--;
//             }
//             free(command);
//             return (NULL);
//         }
//         i++;
//         j++;
//     }
//     return (NULL);
// }


char **ft_join_for_execve(t_list *cmd)
{
    char **command;
    int total;
    int i;
    int j;

    total = 0;
    while (cmd->args[total])
        total++;

    // Allocate memory for total + 1 pointers (including the terminating NULL pointer)
    command = (char **)malloc(sizeof(char *) * (total + 2));
    if (!command)
        return (NULL);

    command[0] = ft_strdup(cmd->value);
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
            free(command[0]); // Free the command[0] before freeing command itself
            free(command);
            return (NULL);
        }
        i++;
        j++;
    }

    // Terminate the command array with a NULL pointer
    command[i] = NULL;

    return (command);
}

// [ ] todo redir to outfile befor exeve() so i gotta fok() even its one cmd

// int execute_one_command(t_list *cmd, t_env *env)
// {
//     char *path;
//     char **command;

//     if (dup2(cmd->infile, 0) == -1)
//         return (-1);
//     path = ft_get_path(cmd, env);
//     if (!path)
//         return (-1);
//     command = ft_join_for_execve(cmd);
//     if (!command)
//         return (-1);
//     execve(path, command, NULL);
//     ft_putstr_fd("command not found: ", 2);
//     ft_putstr_fd(cmd->value, 2);
//     dup2(cmd->outfile, 1);
//     return (0);
// }
