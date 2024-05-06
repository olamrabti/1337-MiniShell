/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:40:06 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/06 14:28:48 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

t_list *handle_doubleq(t_list *curr, int *i)
{
    char *tmp;

    tmp = NULL;
    curr->type = _RM;
    curr = curr->nxt;
    if (curr && curr->type == D_QUOTE)
    {
        (*i)++;
        tmp = ft_strdup("");
        curr->type = _LTRAL;
        free(curr->value);
        curr->value = tmp;
        return curr;
    }
    else if (curr && curr->type != _DOLLAR)
        curr->type = _LTRAL;
    while (curr->nxt && curr->type != D_QUOTE)
    {
        if (curr->type != _DOLLAR && curr->nxt && curr->nxt->type != D_QUOTE)
        {
            if (curr->nxt->type != _DOLLAR && curr->type != Q_DOLLAR)
            {
                tmp = ft_strjoin(curr->value, curr->nxt->value);
                free(curr->value);
                curr->value = tmp;
                delete_node(curr->nxt);
                curr->type = _LTRAL;
            }
            else
                curr->nxt->type = Q_DOLLAR;
        }
        if (curr->type != _DOLLAR)
            curr->type = _LTRAL;
        curr = curr->nxt;
    }
    return curr;
}

t_list *handle_singleq(t_list *curr, int *i)
{
    char *tmp;

    tmp = NULL;
    curr->type = _RM;
    curr = curr->nxt;
    if (curr && curr->type == S_QUOTE)
    {
        tmp = ft_strdup("");
        (*i)++;
        curr->type = _LTRAL;
        free(curr->value);
        curr->value = tmp;
        return curr;
    }
    else if (curr)
        curr->type = _LTRAL;
    while (curr->nxt && curr->type != S_QUOTE)
    {
        if (curr->nxt && curr->nxt->type != S_QUOTE)
        {
            tmp = ft_strjoin(curr->value, curr->nxt->value);
            free(curr->value);
            curr->value = tmp;
            delete_node(curr->nxt);
        }
        curr->type = _LTRAL;
        curr = curr->nxt;
    }
    return curr;
}

int handle_quote(t_list **list, token quote)
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
            curr = handle_singleq(curr, &i);
        }
        else if (curr->type == D_QUOTE && i % 2 == 0)
        {
            i++;
            quote = D_QUOTE;
            curr = handle_doubleq(curr, &i);
        }
        if (curr && curr->type == quote)
        {
            curr->type = _RM;
            i++;
        }
        if (curr)
            curr = curr->nxt;
    }
    remove_token(list, _RM);
    return i;
}
