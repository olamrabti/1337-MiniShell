
#include "parse.h"
#include "../minishell.h"

void ft_join_q(char *tmp, t_list *curr, t_addr **addr)
{
    if (curr && curr->prv && curr->prv->type == WORD)
    {
        tmp = gc_strjoin(curr->prv->value, curr->value, addr);
        curr->prv->value = tmp;
    }
}

void remove_token(t_list **list, token token)
{
    t_list *temp;

    temp = *list;
    while (temp)
    {
        if (temp->type == token)
            delete_node(temp);
        if (temp)
            temp = temp->nxt;
    }
}

int check_syntax(t_list **list, int *count)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr->type == PIPE)
        {
            // FIXME pipe at the beginning deos not work as it should : find a proper condition for it 
            if ((curr->prv && !curr->prv->prv)|| !curr->nxt)
                return printf("syntax error near unexpected token `|'\n"), 1;
            if (curr->nxt && curr->nxt->type == PIPE)
                return printf("syntax error near unexpected token `||'\n"), 1;
        }
        if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == RED_OUT_APPEND)
        {
            (*count)++;
            if ((!curr->nxt))
                return printf("syntax error near unexpected token `newline'\n"), 1;
            if ((curr->nxt && curr->nxt->type != WORD))
                return printf("syntax error near unexpected token `%s'\n", curr->nxt->value), 1;
        }
        if (curr->type == H_DOC)
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

int fill_args(t_list *curr, int count, t_addr **addr)
{
    char **tmp;
    int i;

    // tmp = malloc((count) * sizeof(char *));
    tmp = ft_calloc(addr, count, sizeof(char *));
    if (!tmp)
        return 1;
    tmp[--count] = NULL;
    i = 0;
    while (count)
    {
        if (curr && curr->prv)
        {
            tmp[--count] = curr->value;
            curr->type = RM;
            if (curr->outfile != 1)
                curr->prv->outfile = curr->outfile;
            curr = curr->prv;
        }
        else
            break;
    }
    if (curr)
        curr->args = tmp;
    return 0;
}

void handle_args(t_list **list, t_addr **addr)
{
    t_list *curr;
    int count;

    curr = *list;
    while (curr)
    {
        if (curr && curr->type != PIPE && curr->type != NULL_TOKEN)
        {
            count = 1;
            while (curr && curr->nxt && curr->nxt->type != PIPE)
            {
                count++;
                curr = curr->nxt;
            }
            if (curr && count > 1)
                fill_args(curr, count, addr);
        }
        if (curr)
            curr = curr->nxt;
    }
    remove_token(list, RM);
}

void concat_words(t_list **list, t_addr **addr)
{
    t_list *curr;
    char *tmp;

    curr = *list;
    while (curr)
    {
        if ((curr->type == WORD || curr->type == NF_VAR || curr->type == LTRAL) && curr->nxt 
        && (curr->nxt->type == WORD || curr->nxt->type == NF_VAR || curr->nxt->type == LTRAL))
        {
            tmp = gc_strjoin(curr->value, curr->nxt->value, addr);
            curr->value = tmp;
            if (curr->type == LTRAL || curr->nxt->type == LTRAL)
                curr->type = LTRAL;
            else
                curr->type = WORD;
            delete_node(curr->nxt);
        }
        else
            curr = curr->nxt;
    }
}

int ms_parse(t_data **data, char *line, t_env *env)
{
    t_list *list;
    t_list *last;
    int count;
    int *fds;

    count = 0;
    fds = NULL;
    list = init_list(line, &((*data)->addr));
   
    if (!list)
        return -1;
    if (handle_quote(&list, S_QUOTE, &((*data)->addr)) % 2 != 0)
    {
        expand_all(&list, env, &((*data)->addr));
        printf("quote>\n");
    }
    expand_all(&list, env, &((*data)->addr));
    remove_token(&list, RM);
    concat_words(&list, &((*data)->addr));
    remove_token(&list, W_SPACE);
    if (!check_syntax(&list, &count) && count)
        fds = handle_redirections(&list, &count, &((*data)->addr), env);
    remove_token(&list, RM);
    if (list->nxt)
    {
        list = list->nxt;
        list->first = 1;
        delete_node(list->prv);
    }
    handle_args(&list, &((*data)->addr));
    remove_token(&list, PIPE);
    last = get_last_node(list);
    last->last = 1;
    (*data)->cmd = list;
    (*data)->fds = fds;
    (*data)->status = 0;
    return 0;
}

