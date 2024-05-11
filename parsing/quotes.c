/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:40:06 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/11 10:41:28 by olamrabt         ###   ########.fr       */
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
    if (curr && curr->type == D_QUOTE)
    {
        (*i)++;
        tmp = gc_strdup("", addr);
        curr->type = LTRAL;
        curr->value = tmp;
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
                tmp = gc_strjoin(curr->value, curr->nxt->value, addr);
                curr->value = tmp;
                delete_node(curr->nxt);
                curr->type = LTRAL;
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
        tmp = gc_strdup("", addr);
        (*i)++;
        curr->type = LTRAL;
        curr->value = tmp;
        return curr;
    }
    else if (curr)
        curr->type = LTRAL;
    while (curr && curr->nxt && curr->type != S_QUOTE)
    {
        if (curr->nxt && curr->nxt->type != S_QUOTE)
        {
            tmp = gc_strjoin(curr->value, curr->nxt->value, addr);
            curr->value = tmp;
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
        if (curr && curr->type == quote)
        {
            curr->type = RM;
            i++;
        }
        if (curr)
            curr = curr->nxt;
    }
    remove_token(list, RM);
    return i;
}

