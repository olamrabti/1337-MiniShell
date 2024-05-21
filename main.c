#include "minishell.h"


void ctrl_c_handler(int signum)
{
    if (signum == SIGINT)
    {
        global_signal = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
        rl_on_new_line();
		rl_redisplay();
    }
}

// void ft_signal()
// {
// }

int ft_exit_status(int status)
{
    static int exit_status;

    if (status < 0)
        return (exit_status);
    else
        exit_status = status;
    return (status);
}

int main(int ac, char **av, char **envp)
{
    t_data *data;
    t_env *env;
    char *line;

    (void)ac;
    (void)av;
    rl_catch_signals = 0;
    
    // atexit(f);
    // if (isatty(av[1]))
    //     return (0);
    data = malloc(sizeof(t_data));
    if (!data)
        return (-1);
    data->cmd = NULL;
    data->fds = NULL;
    data->is_hiden = 0;
    data->oldpwd = 1;
    data->save = -1;
    env = ft_parce_env(envp);
    data->env = env;
    data->addr = NULL;
    ft_no_env(&data);
    while (1)
    {
        signal(SIGINT, ctrl_c_handler);
        signal(SIGQUIT, ctrl_c_handler);
        line = readline("MINISHELL$ ");
        if(global_signal)
            ft_exit_status(1);
        if (line == NULL)
        {
            printf("exit\n");
            exit(ft_exit_status(-1));
        }
        if (*line)
            add_history(line);
        if (ms_parse(&data, line, data->env) != 1)
        {
            if (data && data->cmd)
                execute_commands(&data, envp);
        }
        ft_lstclear(&data->addr, free);
        free(line);
        global_signal = 0;
    }
    return 0;
}

