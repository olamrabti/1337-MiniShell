#include "minishell.h"

void ctrl_c_handler(int signum)
{
    (void)signum;
    // if (signum == SIGINT)
    // {
	// 	write(1, "\n", 1);
	// 	rl_replace_line("", 0);
	// 	rl_on_new_line();
	// 	rl_redisplay();
    // }
}

void ft_signal()
{
    // rl_catch_signals = 0;
    // signal(SIGINT, ctrl_c_handler);
    // signal(3, ctrl_c_handler);
}

int main(int ac, char **av, char **envp)
{
    t_data *data;
    t_env *env;
    char *line;

    (void)ac;
    (void)av;
    ft_signal();

    // atexit(f);
    // if (isatty(av[1]))
    //     return (0);

    data = malloc(sizeof(t_data));
    if (!data)
        return (-1);
    data->cmd = NULL;
    data->fds = NULL;
    data->status = 0;
    data->is_hiden = 0;
    data->oldpwd = 1;
    data->save = -1;
    env = ft_parce_env(envp);
    data->env = env;
    data->addr = NULL;
    ft_no_env(&data);
    while (1)
    {
        line = readline("MINISHELL$ ");
        if (line == NULL)
        {
            printf("exit\n");
            exit(0); // [ ] exit with exit_status
        }
        if (*line)
            add_history(line);
        ms_parse(&data, line, data->env); // != 1
        if (data && data->cmd)
            execute_commands(&data, envp);
        

        ft_lstclear(&data->addr, free);
        free(line);
        // printf("\n");
    }
    return 0;
}

