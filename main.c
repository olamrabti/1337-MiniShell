#include "minishell.h"



int main( int ac , char *av[], char**envp)
{
    t_data *data;
    t_env *env;
    char *line;

    (void)ac;
    (void)av;
    data = malloc(sizeof(t_data));
    if(!data)
        return -1;
    data->cmd = NULL;
    data->fds = NULL;
    data->status = 0;
    data->save = -1;
    env = ft_parce_env(envp);
    data->env = env;
    // 
    while (1)
    {
        line = readline("MINISHELL$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        if (ms_parse(&data, line, env))
            return 1;
        if (data &&  data->cmd && data->cmd->type != NULL_TOKEN)
            execute_commands(&data, envp);
        // if (data->cmd)
        //     remove_list(&data->cmd);
        free(line);
        // printf("\n");
    }
    return 0;
}
