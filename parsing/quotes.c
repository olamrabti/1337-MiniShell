/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:40:06 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/23 18:22:47 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

t_list *handle_doubleq(t_list *curr, int *i, t_addr **addr)
{
    char *tmp;

    tmp = NULL;
    curr->type = RM;
    curr = curr->nxt;
    if (curr && curr->type == D_QUOTE) // separate this should be enough for refactoring ( nope tmp is needed)
    {
        (*i)++; // && (*i)++
        tmp = gc_strdup("", addr); // 1 is_emptystr
        curr->type = LTRAL; // 2
        curr->value = tmp; // 3
        return curr;
    }
    else if (curr && curr->type != _DOLLAR)
        curr->type = LTRAL;
    while (curr && curr->nxt && curr->type != D_QUOTE)
    {
        if (curr->type != _DOLLAR && curr->nxt && curr->nxt->type != D_QUOTE)
        {
            if (curr->nxt->type != _DOLLAR && curr->type != Q_DOLLAR)
            {
                tmp = gc_strjoin(curr->value, curr->nxt->value, addr); // or maybe those : 1 join_ltrals
                curr->value = tmp; // 2
                delete_node(curr->nxt);
                curr->type = LTRAL; // 3
            }
        }
        if (curr->type == _DOLLAR)
            curr->type = Q_DOLLAR;
        if (curr->type != _DOLLAR && curr->type != Q_DOLLAR)
            curr->type = LTRAL;
        curr = curr->nxt;
    }
    return curr;
}

t_list *handle_singleq(t_list *curr, int *i, t_addr **addr)
{
    char *tmp;

    tmp = NULL;
    curr->type = RM;
    curr = curr->nxt;
    if (curr && curr->type == S_QUOTE)
    {
        tmp = gc_strdup("", addr); // 1  is_emptystr
        (*i)++;
        curr->type = LTRAL; // 2
        curr->value = tmp; // 3
        return curr;
    }
    else if (curr)
        curr->type = LTRAL;
    while (curr && curr->nxt && curr->type != S_QUOTE)
    {
        if (curr->nxt && curr->nxt->type != S_QUOTE)
        {
            tmp = gc_strjoin(curr->value, curr->nxt->value, addr); // 1  join_ltrals
            curr->value = tmp; // 3 , 2 will not ruin anything if applied here 
            delete_node(curr->nxt);
        }
        curr->type = LTRAL;
        curr = curr->nxt;
    }
    return curr;
}

int handle_quote(t_list **list, token quote, t_addr **addr)
{
    t_list *curr;
    int i;

    curr = *list;
    i = 2;
    while (curr)
    {
        if (curr->type == S_QUOTE && i % 2 == 0)
        {
            i++;
            quote = S_QUOTE;
            curr = handle_singleq(curr, &i, addr);
        }
        else if (curr->type == D_QUOTE && i % 2 == 0)
        {
            i++;
            quote = D_QUOTE;
            curr = handle_doubleq(curr, &i, addr);
        }
        if (curr && curr->type == quote) // && i++; will leave me with 26 lines 
        {
            curr->type = RM;
            i++;
        }
        if (curr)
            curr = curr->nxt;
    }
    remove_token(list, RM); // add it in ms_parse for 25 lines 
    return i;
}

