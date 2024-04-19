/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/19 16:49:45 by olamrabt         ###   ########.fr       */
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
                    printf("->>>>>> curr -%s- type : %d\n", curr->value, curr->type);
                    // here ends the quote, but  it should not merge if s quote encountered
                    ft_join_q(tmp, curr);
                    printf("->>>>>> curr -%s- type : %d\n", curr->value, curr->type);
                    break;
                }
            }
        }
        if (curr && curr->type == S_QUOTE && i % 2 != 0)
        {
            delete_node(curr);
            i++;
            curr = curr->nxt;
            if (curr->type != D_QUOTE)
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

void remove_w_space(t_list **list)
{
    t_list *temp;

    temp = *list;
    while (temp)
    {
        if (temp->type == W_SPACE)
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

void ms_parse(t_list **list, char **envp)
{
    // handle single quotes
    if (handle_sq(list) % 2 != 0)
    {
        printf("quote>\n");
        return;
    }
    expand_all(list, envp);
    // handle double quotes
    if (handle_dq(list, envp) % 2 != 0)
    {
        printf("quote>\n");
        return;
    }
    remove_w_space(list);
    // if (check_tokens(*list) == 1)
    //     return ;
}

// [ ] check for syntax errors in pipe and so ...
// [ ] handle redirections and open files
// [ ] since quotes should escape special characters, should i include a isascii condition ?
// NOTE ''"$HOME" should expand (done)
// NOTE 'ff'"gg" should be joined properly
// int check_tokens(t_list *list)
// {
//     t_list *current;

//     current = list;
//     while (current)
//     {
//         // if | .. must have a word before and after
//         // throw syntax error return -1;
//     }
//     return 0;
// }
