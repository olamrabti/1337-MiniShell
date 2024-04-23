#include "minishell.h"

int main( int ac , char *av[], char**envp)
{
    t_data *data;
    char *line;

    (void)ac;
    (void)av;
    data = NULL;
    while (1)
    {
        line = readline("MINISHELL$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        // if (!ms_parse(data, line, envp))
        // {
        //     // execute_commands(data, envp);
        // }
        ms_parse(data, line, envp);
        remove_list(&data->cmd);
        free(line);
        printf("\n");
    }
    return 0;
}
