#include "execution.h"
#include "../minishell.h"

int ft_execute(t_list *cmd, t_data *data, char **envp)
{
    char *path;
    char **command;
    int i;

    i = 0;
    path = ft_get_path(cmd, data->env, data);
    if (!path)
        return (-1);
    command = ft_join_for_execve(cmd, data->addr);
    if (!command)
        return (-1);
    return (execve(path, command, envp));
}

int *ft_alloc_tab(t_data *data, int *total)
{
    t_list *tmp;
    int *tab;

    tmp = data->cmd;
    while (tmp)
    {
        (*total)++;
        tmp = tmp->nxt;
    }
    tab = ft_calloc(&data->addr, (*total), sizeof(int));
    return (tab);
}

int ft_parent_wait(t_data *data, int *tab, int total, struct termios *term)
{
    int status;
    int i;

    close(data->save);
    i = 0;
    while (i < total)
    {
        waitpid(tab[i], &status, 0);
        i++;
    }
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, term);
        write(1, "Quit: 3\n", 8);
    }
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, term);
        write(1, "\n", 1);
    }
    if (WIFEXITED(status))
        ft_exit_status(WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        ft_exit_status(WTERMSIG(status) + 128);
    return (SUCCESS);
}

int ft_close_descriptors(t_data *data)
{
    int i;

    i = 0;
    if (data && data->fds)
    {
        i = 0;
        while (data->fds[i] > 0)
        {
            close(data->fds[i]);
            i++;
        }
    }
    return (SUCCESS);
}

int ft_pipex(t_data *data, char **envp)
{
    struct termios *term;
    t_list *temp;
    int total;
    int *tab;
    int i;

    (void)envp;
    total = 0;
    term = NULL;
    i = 0;
    tab = ft_alloc_tab(data, &total);
    temp = data->cmd;
    tcgetattr(STDIN_FILENO, term);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    while (temp)
    {
        if (temp->first && temp->last && ft_is_builtin(temp->value))
            return (ft_execute_builtin(temp, data));
        if (temp->first && temp->last && ft_is_a_dir(temp->value) && (ft_strcmp(temp->value, "./minishell") != 0))
            return (ft_handle_dir(temp, data, envp));
        if (!temp->last)
        {
            if (pipe(data->pd) == -1)
                exit(127);
        }
        if (!(temp->type == NULL_TOKEN && temp->infile == 0 && temp->outfile == 1 && temp->last))
            data->pid = fork();
        else
            break;
        if (data->pid == -1)
        {
            perror("fork:");
            return (ERROR);
        }
        tab[i] = data->pid;
        if (data->pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            if (temp->infile != 0)
            {
                if (temp->infile == -1)
                    exit(1);
                if (dup2(temp->infile, 0) == -1)
                    perror("infile");
                close(temp->infile);
            }
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
                if (dup2(data->save, STDIN_FILENO) == -1)
                    return (-1);
                close(data->save);
            }
            if (!temp->last)
            {
                if (dup2(data->pd[1], STDOUT_FILENO) == -1)
                    return (-1);
                close(data->pd[0]);
                close(data->pd[1]);
            }
            if (ft_is_builtin(temp->value))
            {
                ft_execute_builtin(temp, data);
                exit(ft_exit_status(-1));
            }
            else if (ft_is_a_dir(temp->value) && temp->type != NULL_TOKEN)
            {
                ft_handle_dir(temp, data, envp);
                exit(ft_exit_status(-1));
            }
            else
            {
                if (temp->type != NULL_TOKEN)
                {
                    if (ft_execute(temp, data, envp) == -1)
                    {
                        ft_putstr_fd("minishell: ", 2);
                        ft_putstr_fd(temp->value, 2);
                        ft_putstr_fd(" command not found\n", 2);
                        ft_exit_status(127);
                        exit(127);
                    }
                }
                else
                    exit(SUCCESS);
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
    ft_parent_wait(data, tab, total, term);
    return (SUCCESS);
}
