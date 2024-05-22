
#include "execution.h"
#include "../minishell.h"

int ft_execute(t_list *cmd, t_env *env, char **envp, t_addr *addr)
{
    char *path;
    char **command;
    int i;

    i = 0;
    path = ft_get_path(cmd, env);
    if (!path)
        return (-1);
    command = ft_join_for_execve(cmd, addr);
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
    // ft_exit_status(status);
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
            // printf("data->fds[i] ----------> %d\n", data->fds[i]);
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
                if (temp->type != NULL_TOKEN)
                {
                    if (ft_execute(temp, data->env, envp, data->addr) == -1)
                    {
                        ft_putstr_fd("command not found: ", 2);
                        ft_putstr_fd(temp->value, 2);
                        ft_putstr_fd("\n", 2);
                        ft_exit_status(127);
                        exit(127);
                    }
                }
                else
                    exit(EXIT_SUCCESS);
            // else if (ft_is_a_dir(temp->value))
            // {
            //     ft_handle_dir(temp->value);
            //     exit(EXIT_SUCCESS);
            // }
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
