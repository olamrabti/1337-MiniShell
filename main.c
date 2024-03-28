
#include "parsing/parse.h"

int main( int ac , char *av[], char**envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    t_list *list;

    while (1)
    {
        char *line = readline("minishell$ ");
        if (line == NULL)
            break;
        printf("%s\n", line);
        list = ms_tokenize(line, envp);
        print_list(list);
        ms_parse(&list, envp);
        print_list(list);
        remove_list(&list);
        free(line);
    }
    return 0;
}