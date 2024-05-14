
#include "minishell.h"

// void f()
// {
//     system("leaks minishell");
// }

int main(int ac , char **av, char**envp)
{
    t_data *data;
    t_env *env;
    char *line;

    (void)ac;
    (void)av;
    // atexit(f);
    data = malloc(sizeof(t_data));
    if(!data)
        return -1;
    data->cmd = NULL;
    data->fds = NULL;
    data->status = 0;
    data->is_hiden = 0;
    data->save = -1;
    env = ft_parce_env(envp);
    data->env = env;
    data->addr = NULL;
    ft_no_env(&data);
    while (1)
    {
        line = readline("MINISHELL$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        ms_parse(&data, line, env);
        // && data->cmd->type != NULL_TOKEN
        if (data &&  data->cmd)
            execute_commands(&data, envp);
        ft_lstclear(&data->addr, free);
        // print_addr(data->addr);
        // if (data->cmd)
        //     remove_list(&data->cmd);
        free(line);
        // printf("\n");
    }
    return 0;
}
