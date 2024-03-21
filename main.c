
#include "parsing/parse.h"

int main( int ac , char *av[], char**envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    
    while (1)
    {
        char *line = readline("minishell$ ");
        if (line == NULL)
            break;
        printf("%s\n", line);
        free(line);
    }
    return 0;
}