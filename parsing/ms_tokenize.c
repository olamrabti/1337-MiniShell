
#include "parse.h"
#include "../minishell.h"

int is_operator(t_list *current, char *line, int *i, t_addr **addr)
{
    if (line[*i] == '<' && line[*i + 1] == '<')
        return node_addback(&current, create_node(gc_strdup("<<", addr), H_DOC, addr)), *i += 1, 1;
    else if (line[*i] == '>' && line[*i + 1] == '>')
        return node_addback(&current, create_node(gc_strdup(">>", addr), RED_OUT_APPEND, addr)), *i += 1, 1;
    else if (line[*i] == '>')
        return node_addback(&current, create_node(gc_strdup(">", addr), RED_OUT, addr)), 1;
    else if (line[*i] == '<')
        return node_addback(&current, create_node(gc_strdup("<", addr), RED_IN, addr)), 1;
    else if (line[*i] == '|')
        return node_addback(&current, create_node(gc_strdup("|", addr), PIPE, addr)), 1;
    else if (line[*i] == '"')
        return node_addback(&current, create_node(gc_strdup("\"", addr), D_QUOTE, addr)), 1;
    else if (line[*i] == '\'')
        return node_addback(&current, create_node(gc_strdup("'", addr), S_QUOTE, addr)), 1;
    else
        return 0;
}

void is_word(t_list *current, char *line, int *i, t_addr **addr)
{
    current = get_last_node(current);
    if (current && current->type == WORD)
        current->value = ft_charjoin(current->value, line[*i], addr);
    else
        node_addback(&current, create_node(ft_charjoin(NULL, line[*i], addr), WORD, addr));
}

int count_spaces(char *line)
{
    int j;

    j = 1;
    while (line[j] && ft_isspace(line[j]))
        j += 1;
    return j;
}

void ms_tokenize(t_list *current, char *line, t_addr **addr, int *j)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            *j = get_key(line, i, *j);
            if (*j == 1 && line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '"'))
                node_addback(&current, create_node(ft_strndup(&line[i], *j, addr), RM, addr));
            else
                node_addback(&current, create_node(ft_strndup(&line[i], *j, addr), _DOLLAR, addr));
            i += *j - 1;
        }
        else if (ft_isspace(line[i]))
        {
            *j = count_spaces(&line[i]);
            node_addback(&current, create_node(ft_strndup(&line[i], *j, addr), W_SPACE, addr));
            i += *j - 1;
        }
        else if (!is_operator(current, line, &i, addr))
            is_word(current, line, &i, addr);
        i++;
    }
}

t_list *init_list(char *line, t_addr **addr)
{
    t_list *head;
    t_list *current;
    int j;
    j = 1;

    head = create_node(NULL, NULL_TOKEN, addr);
    current = head;
    ms_tokenize(current, line, addr, &j);
    return (head);
}
