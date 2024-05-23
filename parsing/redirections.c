
#include "parse.h"
#include "../minishell.h"


void assign_fd(t_list *tmp, t_addr **addr)
{
    int in;
    int out;

    in = tmp->infile;
    out = tmp->outfile;
    tmp = tmp->nxt;
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            node_add_middle(tmp->prv, create_node(NULL, NULL_TOKEN, addr));
            break;
        }
        if (tmp->type != RM)
        {
            tmp->infile = in;
            tmp->outfile = out;
            break;
        }
        if (!tmp->nxt)
            node_addback(&tmp, create_node(NULL, NULL_TOKEN, addr));
        tmp = tmp->nxt;
    }
}

int *handle_redirections(t_list **list, int *count, t_addr **addr, t_env *env)
{
    t_list *curr;
    t_list *tmp;
    int *fds;
    int i;

    fds = ft_calloc(addr, *count ,sizeof(int));
    if (!fds)
        return NULL;
    fds[*count] = -1;
    curr = *list;
    tmp = *list;
    i = 0;
    while (curr)
    {
        if (curr->type == RED_OUT || curr->type == RED_OUT_APPEND )
        {
            if (curr->type == RED_OUT_APPEND)
                tmp->outfile = open(curr->nxt->value, O_CREAT | O_RDWR | O_APPEND, 0777);
            else
                tmp->outfile = open(curr->nxt->value, O_CREAT | O_RDWR | O_TRUNC, 0777);
            curr->type = RM;
            curr->nxt->type = RM;
            if (tmp->outfile == -1)
                perror(curr->nxt->value);
            fds[i++] = tmp->outfile;
        }
        else if (curr->type == RED_IN)
        {
            tmp->infile = open(curr->nxt->value, O_RDWR);
            curr->type = RM;
            curr->nxt->type = RM;
            if (tmp->infile == -1)
                perror(curr->nxt->value);
            fds[i++] = tmp->infile;
        }
        else if (curr->type == H_DOC)
        {
            curr->type = RM;
            if (curr->nxt && curr->nxt->value)
            {
                tmp->infile = fill_heredoc(curr->nxt, addr, env);
                curr->nxt->type = RM;
            }
            else if (tmp->infile == -1)
                return perror("heredoc"), NULL;
            fds[i++] = tmp->infile;
        }
        if (curr)
            curr = curr->nxt;
        if (!curr || curr->type == PIPE)
        {
            assign_fd(tmp, addr);
            if (curr)
                tmp = curr;
        }
    }
    return fds;
}
