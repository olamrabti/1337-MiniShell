/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/20 11:36:09 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        ft_env();
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

void ft_execute_pipex(t_list *list, t_env *env)
{
    t_list *temp;
    int fd[2];
    int pid;

    temp = list;
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        ft_execute_command(temp->cmd, env);
    }
    else
    {
        waitpid(pid, NULL, 0);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        temp = temp->next;
        ft_execute_command(temp->cmd, env);
    }
}

void ft_execute(t_list *list, t_env *env)
{
    t_list *temp;

    temp = list;
    if (ft_is_one_cmd(temp))
    {
        if (ft_is_builtin(temp))
            ft_execute_builtin(list->cmd, env);
        else
            ft_execute_command(list->cmd, env);
    }
    else
    {
        while (list)
        {
            if (ft_is_builtin(list->cmd))
                ft_execute_builtin(list->cmd, env);
            else
                ft_execute_command(list->cmd, env);
            list = list->next;
        }
    }
}

void ft_execute_redirection(t_list *list, t_env *env)
{
    t_list *temp;
    int fd;

    temp = list;
    if (temp->type == RED_IN)
    {
        fd = open(temp->args, O_RDONLY);
        dup2(fd, 0);
        close(fd);
        ft_execute(temp, env);
    }
    if (temp->type == RED_OUT)
    {
        fd = open(temp->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);
        close(fd);
        ft_execute(temp, env);
    }
    if (temp->type == H_DOC_IN)
    {
        fd = open(temp->args, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);
        close(fd);
        ft_execute(temp, env);
    }
    if (temp->type == H_DOC_OUT)
    {
        fd = open(temp->args, O_RDONLY);
        dup2(fd, 0);
        close(fd);
        ft_execute(temp, env);
    }
}

void ft_execute_pipe(t_list *list, t_env *env)
{
    t_list *temp;
    int fd[2];
    int pid;

    temp = list;
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        ft_execute_redirection(temp, env);
    }
    else
    {
        waitpid(pid, NULL, 0);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        temp = temp->next;
        ft_execute_redirection(temp, env);
    }
}

void ft_execute_list(t_list *list, t_env *env)
{
    t_list *temp;

    temp = list;
    if (temp->type == _PIPE)
        ft_execute_pipe(temp, env);
    else
        ft_execute_redirection(temp, env);
}

