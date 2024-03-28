/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/03/03 18:09:53 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int  handle_single_quotes(t_list **list)
{
    t_list *current;
    char *tmp;
    int i;


    current = *list;
    i = 2;
    while (current)
    {
        if (current->type == S_QUOTE && i % 2 == 0)
        {
            i++;
            while (current->nxt && current->nxt->type != S_QUOTE)
            {
                tmp = ft_strjoin(current->value, current->nxt->value);
                free(current->value);
                free(current->nxt->value);
                free(current->nxt);
                current->value = tmp;
                current->type = _WORD;
                current->nxt = current->nxt->nxt;
            }
            if (current->nxt->type == S_QUOTE)
            {
                tmp = ft_strjoin(current->value, current->nxt->value);
                free(current->value);
                free(current->nxt->value);
                free(current->nxt);
                current->value = tmp;
                current->type = _WORD;
                current->nxt = current->nxt->nxt;
            }
        }
        if (current->type == S_QUOTE && i % 2 != 0)
            i++;
        else
            current = current->nxt;
    }
    return i;
}

int handle_double_quotes(t_list **list, char **envp)
{
    t_list *current;
    char *tmp;
    int i;

    current = *list;
    i = 0;
    while (current)
    {
        if (current->type == D_QUOTE && i % 2 == 0)
        {
            i++;
            while (current->nxt && current->nxt->type != D_QUOTE)
            {
                tmp = ft_expand_dollar(current->value, envp);
                if (tmp == NULL)
                    return 1;
                free(current->value);
                free(current->nxt->value);
                free(current->nxt);
                current->value = tmp;
                current->type = _WORD;
                current->nxt = current->nxt->nxt;
            }
            if (current->nxt->type == D_QUOTE)
            {
                tmp = ft_expand_dollar(current->value, envp);
                if (tmp == NULL)
                    return 1;
                free(current->value);
                free(current->nxt->value);
                free(current->nxt);
                current->value = tmp;
                current->type = _WORD;
                current->nxt = current->nxt->nxt;
            }
        }
        if (current->type == D_QUOTE && i % 2 != 0)
            i++;
        else
            current = current->nxt;
    }
    return i;
}

void ms_parse(t_list **list, char **envp)
{
    // handle single quotes
    if (handle_single_quotes(list) == 1)
        return ;
    // handle double quotes
    if (handle_double_quotes(list, envp) == 1)
        return ;
}