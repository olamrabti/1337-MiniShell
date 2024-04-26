#include "minishell.h"

int main( int ac , char *av[], char**envp)
{
    t_data *data;
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
    // 
    while (1)
    {
        line = readline("MINISHELL$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        ms_parse(&data, line, envp);
        execute_commands(&data, envp);
        // ms_parse(data, line, envp);
        // remove_list((*data)->cmd);
        free(line);
        printf("\n");
    }
    return 0;
}
