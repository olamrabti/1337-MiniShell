
#include "parsing/parse.h"

int main( int ac , char *av[], char**envp)
{
    (void)ac;
    (void)av;
    t_list *list;
    int status;

    status = 0;
    while (1)
    {
        char *line = readline("minishell$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        list = ms_tokenize(line, envp);
        if (!list)
            break ;
        ms_parse(&list, envp);
        print_list(list);
        if (status)
            exit(status);
        // execute_commands(data, envp, status);
        // if (status)
        //     exit(status);
        remove_list(&list);
        free(line);
    }
    return 0;
}
