#include "parse.h"
#include "../minishell.h"

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

int check_syntax(t_list **list, int *count)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr->type == PIPE)
        {
            if ((curr->prv && !curr->prv->prv) || !curr->nxt)
                return printf("syntax error near unexpected token `|'\n"), 1;
            if (curr->nxt && curr->nxt->type == PIPE)
                return printf("syntax error near unexpected token `||'\n"), 1;
        }
        if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == RED_OUT_APPEND || curr->type == H_DOC)
        {
            (*count)++;
            if ((!curr->nxt))
                return printf("syntax error near unexpected token `newline'\n"), 1;
            if ((curr->nxt && curr->nxt->type != WORD && curr->nxt->type != LTRAL))
                return printf("syntax error near unexpected token `%s'\n", curr->nxt->value), 1;
        }
        curr = curr->nxt;
    }
    return 0;
}
