
#include "parsing/parse.h"

int main( int ac , char *av[], char**envp)
{
    (void)ac;
    (void)av;
    t_list *list;

    while (1)
    {
        char *line = readline("minishell$ ");
        if (line == NULL)
            break;
        if (*line)
            add_history(line);
        printf("%s\n", line);
        list = ms_tokenize(line, envp);
        if (!list)
            break ;
        print_list(list);
        ms_parse(&list, envp);
        printf("-------Parsed:--------\n");
        print_list(list);
        remove_list(&list);
        free(line);
    }
    return 0;
}