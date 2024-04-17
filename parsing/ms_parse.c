/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/17 14:29:52 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// [x] do not include single quotes in the word.
int  handle_sq(t_list **list)
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
                if (!curr->nxt)
                {
                    curr->type = _WORD;
                    break ;
                }
                if (curr->nxt && curr->nxt->type == S_QUOTE)
                    break ;
                tmp = ft_strjoin(curr->value, curr->nxt->value);
                free(curr->value);
                delete_node(curr->nxt);
                curr->value = tmp;
                curr->type = _WORD;
            }
        }
        if (curr && curr->type == S_QUOTE && i % 2 != 0)
            i++;
        else if (curr)
            curr = curr->nxt;
    }
    return i;
}

// [ ] do not include double quotes in the word.
// [ ] WHEN $ is proceeded by none double quote it doesnt expand (figure out why) 
int handle_dq(t_list **list, char **envp)
{
    t_list *curr;
    char *tmp;
    int i;

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
                printf("cuurr value -%s-  type : %d\n",curr->value, curr->type);
                if (curr && curr->type == _DOLLAR)
                {
                    tmp = ft_strdup(ft_expand(curr->value, envp));
                    printf("tmp : %s\n", tmp);
                    free(curr->value);
                    curr->value = tmp;
                }
                if (!curr->nxt)
                {
                    curr->type = _WORD;
                    break ;
                }
                if (curr->nxt && curr->nxt->type == D_QUOTE)
                    break ;
                tmp = ft_strjoin(curr->value, curr->nxt->value);
                free(curr->value);
                delete_node(curr->nxt);
                curr->value = tmp;
                curr->type = _WORD;
            }
        }
        if (curr && curr->type == D_QUOTE && i % 2 != 0)
            i++;
        else if (curr)
            curr = curr->nxt;
    }
    return i;
}

void ms_parse(t_list **list, char **envp)
{
    // handle single quotes
    if (handle_sq(list) % 2 != 0)
    {
        printf("quote>\n");
        return ;
    }
    // handle double quotes
    if (handle_dq(list, envp) == 1)
        return ;
    // if (check_tokens(*list) == 1)
    //     return ;
}

// int check_tokens(t_list *list)
// {
//     t_list *current;

//     current = list;
//     while (current)
//     {
//         // if | .. 
//         // throw syntax error 
//     }
//     return 0;
// }
