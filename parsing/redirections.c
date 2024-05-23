
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

int open_file(t_list *curr, t_list *tmp, t_addr **addr, t_env *env)
{
    if (tmp->infile >= 0 && tmp->outfile > 0 && (curr->type == RED_OUT || curr->type == RED_OUT_APPEND))
    {
        if (curr->type == RED_OUT_APPEND)
            tmp->outfile = open(curr->nxt->value, O_CREAT | O_RDWR | O_APPEND, 0644);
        else
            tmp->outfile = open(curr->nxt->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (tmp->outfile == -1)
            return perror(curr->nxt->value), empty_cmd(curr, addr, env), tmp->outfile;
        return curr->type = RM, curr->nxt->type = RM, tmp->outfile;
    }
    if (tmp->infile >= 0 && tmp->outfile > 0 && curr->type == RED_IN)
    {
        tmp->infile = open(curr->nxt->value, O_RDWR);
        if (tmp->infile == -1)
            return perror(curr->nxt->value), empty_cmd(curr, addr, env), tmp->infile;
        return curr->type = RM, curr->nxt->type = RM, tmp->infile;
    }
    curr->type = RM;
    curr->nxt->type = RM;
    return -1;
}
int open_heredoc(t_list *curr, t_list *tmp, t_addr **addr, t_env *env)
{
    curr->type = RM;
    tmp->infile = fill_heredoc(curr->nxt, addr, env);
    curr->nxt->type = RM;
    return tmp->infile;
}

int *handle_redirections(t_list **list, int *count, t_data **data , t_env *env)
{
    t_list *curr;
    t_list *tmp;
    int i;
   
    (*data)->fds[*count] = -1;
    curr = *list;
    tmp = *list;
    i = 0;
    while (curr)
    {
        if ((curr->type == RED_OUT || curr->type == RED_OUT_APPEND || curr->type == RED_IN))
            (*data)->fds[i++] = open_file(curr, tmp, &(*data)->addr, env);
        else if (curr->type == H_DOC)
            (*data)->fds[i++] = open_heredoc(curr, tmp, &(*data)->addr, env);
        curr = curr->nxt;
        if (!curr || curr->type == PIPE)
        {
            assign_fd(tmp, &(*data)->addr);
            if (curr)
                tmp = curr;
        }
    }
    return (*data)->fds;
}
