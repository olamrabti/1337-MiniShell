
#include "parsing.h"

int main( int ac , char *av[])
{
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