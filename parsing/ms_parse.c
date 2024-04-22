/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/22 12:09:46 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void ft_join_q(char *tmp, t_list *curr)
{
    if (curr && curr->prv && curr->prv->type == _WORD)
    {
        tmp = ft_strjoin(curr->prv->value, curr->value);
        curr->prv->value = tmp;
        delete_node(curr);
    }
}

int handle_sq(t_list **list)
{
    t_list *curr;
    char *tmp;
    int i;

    curr = *list;
    i = 2;
    while (curr)
    {
        if (curr->type == S_QUOTE && i % 2 == 0)
        {
            delete_node(curr); // frees but doesnt move to the next node
            curr = curr->nxt;
            i++;
            while (curr && curr->type != S_QUOTE)
            {
                if (curr->nxt && curr->nxt->type != S_QUOTE)
                {
                    tmp = ft_strjoin(curr->value, curr->nxt->value);
                    free(curr->value);
                    curr->value = tmp;
                    delete_node(curr->nxt);
                }
                curr->type = _WORD;
                if (!curr->nxt || curr->nxt->type == S_QUOTE)
                {
                    ft_join_q(tmp, curr);
                    break;
                }
            }
        }
        if (curr && curr->type == S_QUOTE && i % 2 != 0)
        {
            delete_node(curr);
            i++;
            curr = curr->nxt;
            if (curr && curr->type != D_QUOTE)
                ft_join_q(tmp, curr);
        }
        else
            curr = curr->nxt;
    }
    return i;
}

int handle_dq(t_list **list, char **envp)
{
    t_list *curr;
    char *tmp;
    int i;

    (void)envp;
    curr = *list;
    i = 0;
    while (curr)
    {
        if (curr->type == D_QUOTE && i % 2 == 0)
        {
            delete_node(curr); // frees but doesnt move to the next node
            curr = curr->nxt;
            i++;
            while (curr && curr->type != D_QUOTE)
            {
                if (curr->nxt && curr->nxt->type != D_QUOTE)
                {
                    // if (curr->nxt && curr->nxt->type == _DOLLAR)
                    // {
                    //     tmp = ft_expand(curr->nxt->value, envp);
                    //     free(curr->nxt->value);
                    //     curr->nxt->value = tmp;
                    // }
                    tmp = ft_strjoin(curr->value, curr->nxt->value);
                    free(curr->value);
                    curr->value = tmp;
                    delete_node(curr->nxt);
                }
                curr->type = _WORD;
                if (!curr->nxt || curr->nxt->type == D_QUOTE)
                {
                    ft_join_q(tmp, curr);
                    break;
                }
            }
        }
        if (curr && curr->type == D_QUOTE && i % 2 != 0)
        {
            delete_node(curr);
            i++;
            curr = curr->nxt;
            ft_join_q(tmp, curr);
        }
        else if (curr)
            curr = curr->nxt;
    }
    return i;
}

void remove_token(t_list **list, token token)
{
    t_list *temp;

    temp = *list;
    while (temp)
    {
        if (temp->type == token)
            delete_node(temp);
        temp = temp->nxt;
    }
}

void expand_all(t_list **list, char **envp)
{
    t_list *curr;
    char *tmp;

    curr = *list;
    while (curr)
    {
        if (curr->type == _DOLLAR)
        {
            tmp = ft_expand(curr->value, envp);
            free(curr->value);
            curr->value = tmp;
            curr->type = _WORD;
        }
        curr = curr->nxt;
    }
}


// [ ] handle redirections and open files (last in assign to infile and last out assign it to outfile for each command)
// [ ] handle heredoc 
// [ ] since quotes should escape special characters, should i include a isascii condition ?

int check_syntax(t_list **list)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr->type == _PIPE)
        {
            if ((!curr->prv || curr->prv->type != _WORD) 
                || (!curr->nxt || curr->nxt->type != _WORD))
                return printf("invalid PIPE syntax\n"), -1;
        }
        if (curr->type == RED_IN || curr->type == RED_OUT 
            || curr->type == H_DOC_APPEND)
        {
            if ((!curr->nxt || curr->nxt->type != _WORD))
                return printf("invalid RED or H_DOC_APP syntax\n"), -1;
        }
        if (curr->type == H_DOC_TRUNC 
            && (!curr->nxt || curr->nxt->type != _WORD))
            return printf("invalid H_DOC_TRUNC syntax\n"), -1;
        curr = curr->nxt;
    }
    return 0;
}
void handle_args(t_list **list)
{
    t_list *curr;

    curr = *list;
    
    while(curr)
    {
        if (curr->type == _WORD && curr->prv && curr->prv->type == _WORD)
        {
            if (curr->prv->args)
            {
                curr->prv->args = ft_strjoin(curr->prv->args, " ");
                curr->prv->args = ft_strjoin(curr->prv->args, curr->value);
            }
            else
                curr->prv->args = ft_strdup(curr->value);
            free(curr->value);
            delete_node(curr);
        }
        curr = curr->nxt;
    }
    
}


void ms_parse(t_list **list, char **envp)
{
    if (handle_sq(list) % 2 != 0)
    {
        printf("quote>\n");
        return;
    }
    expand_all(list, envp);
    if (handle_dq(list, envp) % 2 != 0)
    {
        printf("quote>\n");
        return;
    }
    remove_token(list, W_SPACE);
    if (check_syntax(list) == 1)
        return;
    // open_fds();
    handle_args(list);
    remove_token(list, _PIPE);
}

//  printf("--\n");
//             if (curr->nxt)
//                 printf("curr nxt -%s- type: %d\n", curr->nxt->value, curr->nxt->type);
//             if (curr->prv)
//                 printf("curr prv -%s- type: %d\n", curr->prv->value, curr->prv->type);