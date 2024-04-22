/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/21 15:56:24 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// [ ]: check if the command is a builtin
// [ ]: execute the builtin
// [ ] pipex

void ft_execute_builtin(char *cmd, t_env *env)
{
    if (ft_strncmp(cmd, "echo", 4) == 0)
        ft_echo();
    if (ft_strncmp(cmd, "cd", 2) == 0)
        ft_cd();
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        ft_pwd();
    if (ft_strncmp(cmd, "export", 6) == 0)
        ft_export();
    if (ft_strncmp(cmd, "unset", 5) == 0)
        ft_unset();
    if (ft_strncmp(cmd, "env", 3) == 0)
        // ft_env();
    if (ft_strncmp(cmd, "exit", 4) == 0)
        ft_exit();
}

void ft_execute_command(char *cmd, t_env *env)
{
    char **args;
    char *path;
    int i;

    args = ft_split(cmd, ' ');
    path = ft_get_path(env);
    i = 0;
    while (path[i])
    {
        if (access(path[i], X_OK) == 0)
        {
            execve(path[i], args, env->env);
            perror("execve");
            exit(1);
        }
        i++;
    }
    perror("command not found");
    exit(1);
}



