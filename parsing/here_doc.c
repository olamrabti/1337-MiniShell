
#include "parse.h"
#include "../minishell.h"

void expand_inside_str(char *line, t_addr **addr, t_env *env, int fd)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 1;
    tmp = NULL;
    if (!line)
        return;
    while (line[i])
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

void h_doc_handler(int signum)
{
    if (signum == SIGINT)
    {
        global_signal = 1;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        ft_exit_status(1);
    }
}

int fill_heredoc(t_list *deli, t_addr **addr, t_env *env)
{
    char *line;
    int fd[2];

    if (!deli || pipe(fd) < 0)
        return -1;
    signal(SIGINT, h_doc_handler);
    signal(SIGQUIT, ctrl_c_handler);
    while (1)
    {
        if (global_signal)
            return close(fd[1]), close(fd[0]), -1;
        line = readline("> ");
        if (!line || !ft_strcmp(line, deli->value))
        {
            free(line);
            break;
        }
        if (deli->type != LTRAL)
            expand_inside_str(line, addr, env, fd[1]);
        else
            write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    return close(fd[1]), fd[0];
}
