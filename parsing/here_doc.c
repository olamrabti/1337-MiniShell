
#include "parse.h"
#include "../minishell.h"

// create the file to write into

int open_heredoc(int tmp, t_addr **addr)
{
    char *filename;
    char i;

    i = '1';
    filename = gc_strdup("h_doc", addr);
    // something wrong here, am tired
    while (1)
    {
        if (access(filename, X_OK | R_OK | F_OK) == -1)
            filename = ft_charjoin(filename, i++, addr);
        if (i == 57)
            break;
        // i = 49;
    }
    tmp = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
    // free(filename);
    if (tmp < 0)
        return -1;
    unlink(filename);
    return tmp;
}

// open readline and wait for delimiter

int fill_heredoc(int tmp, char *deli, t_addr **addr)
{
    char *line;
    // int fd;

    // fd = -1;
    if (!deli)
        return -1;
    // fd = open_heredoc(fd);
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (!ft_strcmp(line, deli))
            break ;
        // if delimiter is not literal , expand before write
        line = ft_charjoin(line, '\n', addr);
        write(tmp, line, ft_strlen(line));
        // free(line);
    }
    return tmp;
}
