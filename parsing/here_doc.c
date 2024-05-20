
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
    int	fd[2];

    if (!deli)
        return -1;
	if (pipe(fd) < 0)
		return (perror("Heredoc pipe "), -1);
    while (1)
    {
        line = readline("> ");
        signal(SIGINT, ctrl_c_handler);
        signal(3, ctrl_c_handler);
        if (line == NULL)
            break;
        if (!ft_strcmp(line, deli->value))
            break ;
        if (deli->type != LTRAL)
            expand_inside_str(line, addr, env, fd[1]);
        else
            write(fd[1], line, ft_strlen(line));
        // if ctrl + D dont add \n, maybe !
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    return fd[0];
}
