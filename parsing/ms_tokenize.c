
#include "parse.h"
#include "../minishell.h"

int ft_isprint(int c)
{
    if (c >= 32 && c < 127)
        return (1);
    return (0);
}

int ft_isdigit(int d)
{
    if (d >= '0' && d <= '9')
        return (1);
    return (0);
}
int ft_isspace(int d)
{
    if (d == ' ' || (d >= 9 && d <= 13))
        return (1);
    return (0);
}
int ft_isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int ft_isalnum(int c)
{
    if (ft_isalpha(c) || ft_isdigit(c))
        return (1);
    return (0);
}


t_list *ms_tokenize(char *line, t_addr **addr)
{
    t_list *head;
    t_list *current;
    int i;
    int j;

    head = create_node(NULL, NULL_TOKEN, addr);
    current = head;
    i = 0;
    j = 1;
    while (line[i])
    {
        if (line[i] == '<' && line[i + 1] == '<')
        {
            node_addback(&current, create_node(ft_strdup("<<"), H_DOC, addr));
            i++;
        }
        else if (line[i] == '>' && line[i + 1] == '>')
        {
            node_addback(&current, create_node(ft_strdup(">>"), RED_OUT_APPEND, addr));
            i++;
        }
        else if (line[i] == '>')
            node_addback(&current, create_node(ft_strdup(">"), RED_OUT, addr));
        else if (line[i] == '<')
            node_addback(&current, create_node(ft_strdup("<"), RED_IN, addr));
        else if (line[i] == '|')
            node_addback(&current, create_node(ft_strdup("|"), _PIPE, addr));
        else if (line[i] == '"')
            node_addback(&current, create_node(ft_strdup("\""), D_QUOTE, addr));
        else if (line[i] == '\'')
            node_addback(&current, create_node(ft_strdup("'"), S_QUOTE, addr));
        else if (line[i] == '$')
        {
            j = get_key(line, i, j);
            node_addback(&current, create_node(ft_strndup(&line[i], j), _DOLLAR, addr));
            i += j - 1;
        }
        else if (ft_isspace(line[i]))
        {
            j = 1;
            while ((line[i + j]) && ft_isspace(line[i + j]))
                j++;
            node_addback(&current, create_node(ft_strndup(&line[i], j), W_SPACE, addr));
            i += j - 1;
        }
        else
        {
            current = get_last_node(current);
            if (current && current->type == _WORD)
                current->value = ft_charjoin(current->value, line[i]);
            else
                node_addback(&current, create_node(ft_charjoin(NULL, line[i]), _WORD, addr));
        }
        i++;
    }
    return (head);
}
