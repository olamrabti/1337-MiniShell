/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/26 10:31:19 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

void ft_join_q(char *tmp, t_list *curr)
{
    if (curr && curr->prv && curr->prv->type == _WORD)
    {
        tmp = ft_strjoin(curr->prv->value, curr->value);
        curr->prv->value = tmp;
    }
}

int handle_quote(t_list **list, token quote)
{
    t_list *curr;
    char *tmp;
    int i;

    curr = *list;
    i = 2;
    while (curr)
    {
        if (curr->type == S_QUOTE && i % 2 == 0)
            quote = S_QUOTE;
        if (curr->type == D_QUOTE && i % 2 == 0)
            quote = D_QUOTE; 
        if (curr->type == quote && i % 2 == 0)
        {
            delete_node(curr);
            curr = curr->nxt;
            i++;
            if (quote == S_QUOTE)
            {
                while (curr && curr->type != quote)
                {
                    if (curr->nxt && curr->nxt->type != quote)
                    {
                        tmp = ft_strjoin(curr->value, curr->nxt->value);
                        free(curr->value);
                        curr->value = tmp;
                        delete_node(curr->nxt);
                    }
                    curr->type = _WORD;
                    curr = curr->nxt;
                }
            }
            else
            {
                while (curr && curr->type != quote)
                {
                    if (curr->type != _DOLLAR && curr->nxt && curr->nxt->type != quote)
                    {
                        if (curr->nxt->type != _DOLLAR)
                        {
                            tmp = ft_strjoin(curr->value, curr->nxt->value);
                            free(curr->value);
                            curr->value = tmp;
                            delete_node(curr->nxt);
                            curr->type = _WORD;
                        }
                    }
                    if (curr->type != _DOLLAR)
                        curr->type = _WORD;
                    curr = curr->nxt;
                }
            }
            if (curr && curr->type == quote)
            {
                delete_node(curr);
                i++;
            }
        }
        if (curr && curr->type == quote && i % 2 != 0)
            i++;
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
        {
            // free(temp->value); this could be necessary
            delete_node(temp);
        }
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

int check_syntax(t_list **list)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr->type == _PIPE)
        {
            if ((!curr->prv || curr->prv->type != _WORD) || (!curr->nxt || curr->nxt->type != _WORD))
                return printf("invalid PIPE syntax\n"), -1;
        }
        if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == H_DOC_APPEND)
        {
            if ((!curr->nxt || curr->nxt->type != _WORD))
                return printf("invalid RED or H_DOC_APP syntax\n"), -1;
        }
        if (curr->type == H_DOC_TRUNC && (!curr->nxt || curr->nxt->type != _WORD))
            return printf("invalid H_DOC_TRUNC syntax\n"), -1;
        curr = curr->nxt;
    }
    return 0;
}

int fill_args(t_list *curr, int count)
{
    char **tmp;
    int i;

    tmp = malloc((count) * sizeof(char *));
    if (!tmp)
        return 1;
    tmp[--count] = NULL;
    i = 0;
    while (count)
    {
        tmp[--count] = curr->value;
        curr->type = _RM;
        curr = curr->prv;
    }
    curr->args = tmp;
    return 0;
}

void handle_args(t_list **list)
{
    t_list *curr;
    int count;

    curr = *list;
    while (curr)
    {
        count = 0;
        while (curr && curr->type == _WORD && curr->type != NULL_TOKEN)
        {
            count++;
            curr = curr->nxt;
        }
        if (curr && count > 1 && fill_args(curr->prv, count))
            printf("parsing : filling args failed\n");
        if (curr)
            curr = curr->nxt;
    }
    remove_token(list, _RM);
}

void concat_words(t_list **list)
{
    t_list *curr;
    char *tmp;

    curr = *list;
    while (curr)
    {
        if (curr->type == _WORD && curr->nxt && curr->nxt->type == _WORD)
        {
            tmp = ft_strjoin(curr->value, curr->nxt->value);
            free(curr->value);
            curr->value = tmp;
            delete_node(curr->nxt);
        }
        else 
            curr = curr->nxt;
    }
    remove_token(list, W_SPACE);
}

int ms_parse(t_data *data, char *line, char **envp)
{
    t_list *list;

    list = ms_tokenize(line, envp);
    if (!list)
        return -1;
    print_list(list);
    if (handle_quote(&list, S_QUOTE) % 2 != 0)
    {
        expand_all(&list, envp);
        print_list(list);
        return printf("quote>\n"), -1;
    }
    expand_all(&list, envp);
    concat_words(&list);
    if (check_syntax(&list) == 1)
        return -1;
    // open_fds();
    // handle_args(&list);
    remove_token(&list, _PIPE);
    data = malloc(sizeof(t_data));
    if (!data)
        return -1;
    data->cmd = list;
    data->fds = NULL;
    data->status = 0;
    printf("\nfinal result : \n");
    print_list(list);
    return 0;
}

//  printf("--\n");
//             if (curr->nxt)
//                 printf("curr nxt -%s- type: %d\n", curr->nxt->value, curr->nxt->type);
//             if (curr->prv)
//                 printf("curr prv -%s- type: %d\n", curr->prv->value, curr->prv->type);