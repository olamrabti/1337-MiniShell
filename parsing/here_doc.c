
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

void expand_inside_str(char *line, t_addr **addr, t_env *env, int fd)
{
    int i;
    int j; 
    char *tmp;

    i = 0;
    j = 1;
    tmp = NULL;
    if (!line)
        return ;
    while(line[i])
    {
        if (line[i] == '$')
        {
            j = get_key(line, i, j);
            tmp = ft_strndup(&line[i], j, addr);
            tmp = ft_expand(tmp, env, addr);
            if (tmp)
                write(fd, tmp, ft_strlen(tmp));
            i += j;
        }
        else 
            write(fd, &line[i++], 1);
    }
}

int fill_heredoc(t_list *deli, t_addr **addr, t_env *env)
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
        if (!ft_strcmp(line, deli->value))
            break ;
        // if delimiter is not literal , expand before write
        if (deli->type != LTRAL)
            expand_inside_str(line, addr, env, fd);
        else
            write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    fd2 = open(filename, O_RDWR, 0666);
    // unlink(filename);
    return fd2;
}
