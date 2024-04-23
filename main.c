#include "minishell.h"

int main( int ac , char *av[], char**envp)
{
    t_list *list;
    t_data *data = NULL;
    char *line;

    (void)ac;
    (void)av;
    while (1)
    {
        line = readline("minishell$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        list = ms_tokenize(line, envp);
        if (!list)
            break ;
        ms_parse(&list, envp);
        // print_list(list);
        execute_commands(data, envp);
        remove_list(&list);
        free(line);
    }
    return 0;
}
