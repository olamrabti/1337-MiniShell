
#include "parse.h"
#include "../minishell.h"


int open_heredoc(char **filename, int tmp, t_addr **addr)
{
    
    char i;

    i = '1';
    *filename = gc_strdup("/tmp/h_doc", addr);
    tmp = open(*filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
    while (tmp < 0 && !access(*filename, X_OK | R_OK | F_OK))
    {
        *filename = ft_charjoin(*filename, i++, addr);
        tmp = open(*filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
        if (i == 57)
            i = 49;
    }
    if (tmp < 0)
        return -1;
    // unlink(filename);
    return tmp;
}


int fill_heredoc(char *deli, t_addr **addr)
{
    char *line;
    char *filename;
    int fd;
    int fd2;

    fd = -1;
    if (!deli)
        return -1;
    fd = open_heredoc(&filename, fd, addr);
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (!ft_strcmp(line, deli))
            break ;
        // if delimiter is not literal , expand before write
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    fd2 = open(filename, O_RDWR, 0666);
    // unlink(filename);
    return fd2;
}
