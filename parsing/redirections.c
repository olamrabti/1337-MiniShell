
#include "parse.h"
#include "../minishell.h"


int is_valid_name(char *str)
{
    int i;
    
    i = 0;
    if(!str)
        return 1;
    // [ ] Check for valid name rules
    while(str[i] && ft_isprint(str[i]) && !ft_isspace(str[i++]))
    ;
    if (str[i])
        return 1;
    return 0;
}
int *handle_redirections(t_list **list, int *count, t_addr **addr)
{
    t_list *curr;
    int *fds;
    int tmp;
    int i;

    fds = malloc(sizeof(sizeof(int)) * (*count));
    if (!fds)
        return NULL;
    fds[*count]= -1;
    curr = *list;
    i = 0;
    while (curr)
    {
        tmp = -1;
        if (curr->type == RED_OUT || curr->type == RED_OUT_APPEND) // > >> ; cmd > filename
        {
            // delete_node(curr);
            curr->type = RM;
            if (curr->nxt && !is_valid_name(curr->nxt->value))
            {
                if (curr->type == RED_OUT_APPEND)
                    tmp = open(curr->nxt->value, O_CREAT | O_RDWR | O_APPEND, 0777);
                else
                    tmp = open(curr->nxt->value, O_CREAT | O_RDWR | O_TRUNC, 0777);
                curr->nxt->type = RM;
                if (tmp != -1 && curr->prv)
                    curr->prv->outfile = tmp;
                else if (tmp == -1)
                    return perror(curr->nxt->value), NULL;
                fds[i++] = tmp;
                // delete_node(curr->nxt);
            }
            else
                return printf("invalid name for fd\n"), NULL;
        } 
        else if (curr->type == RED_IN)
        {
            // delete_node(curr);
            curr->type = RM;
            if (curr->nxt && !is_valid_name(curr->nxt->value))
            {
                if (curr->nxt->type == NF_VAR)
                    return printf("infile : ambiguous redirect"), NULL;
                tmp = open(curr->nxt->value, O_RDWR);
                curr->nxt->type = RM;
                if (tmp != -1 && curr->nxt->nxt)
                    curr->nxt->nxt->infile = tmp;
                else if (tmp == -1 )
                    return perror(curr->nxt->value), NULL;
                fds[i++] = tmp;
                // delete_node(curr->nxt);
            }
            else
                return printf("invalid name for fd\n"), NULL;
        }
        else if (curr->type == H_DOC)
        {
            // delete_node(curr);
            curr->type = RM;
            tmp = open_heredoc(tmp, addr);
            if (curr->nxt && curr->nxt->value)
            {
                fill_heredoc(tmp, curr->nxt->value, addr);
                curr->nxt->type = RM;
            }
            if (tmp != -1 && curr->nxt->nxt)
                curr->nxt->nxt->infile = tmp;
            else if (tmp == -1)
                return perror("heredoc error "), NULL;
            fds[i++] = tmp;
            // delete_node(curr->nxt);
        }
        if (curr)
            curr = curr->nxt;
    }
    return fds;
}
