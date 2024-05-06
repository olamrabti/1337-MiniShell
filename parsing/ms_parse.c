/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/06 15:52:12 by olamrabt         ###   ########.fr       */
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


int check_syntax(t_list **list, int *count)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr->type == _PIPE)
        {
            if ((!curr->prv || curr->prv->type != _WORD) || (!curr->nxt || curr->nxt->type != _WORD))
                return printf("invalid PIPE syntax\n"), 1;
        }
        if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == RED_OUT_APPEND)
        {
            (*count)++;
            if (curr->nxt && curr->nxt->type == NF_VAR)
                return printf("ambiguous redirect\n"), 1;
            if ((!curr->nxt || curr->nxt->type != _WORD))
                return printf("invalid RED or H_DOC_APP syntax\n"), 1;
        }
        if (curr->type == H_DOC)
        {
            (*count)++;
            if ((!curr->nxt))
                return printf("invalid H_DOC syntax\n"), 1;
            if ((curr->nxt && curr->nxt->type != _WORD && curr->nxt->type != _LTRAL))
                return printf("invalid H_DOC syntax\n"), 1;
        }
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
        if (curr->outfile != 1)
            curr->prv->outfile = curr->outfile;
        // if (curr->infile != 0)
        //     curr->prv->infile = curr->infile;
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
        count = 1;
        while (curr && (curr->type == _WORD || curr->type == _LTRAL) 
            && curr->nxt && (curr->nxt->type == _WORD || curr->nxt->type == _LTRAL))
        {
            count++;
            curr = curr->nxt;
        }
        if (curr && count > 1 && fill_args(curr, count))
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
        if ((curr->type == _WORD || curr->type == NF_VAR || curr->type == _LTRAL) 
        && curr->nxt && (curr->nxt->type == _WORD || curr->nxt->type == NF_VAR || curr->nxt->type == _LTRAL))
        {
            tmp = ft_strjoin(curr->value, curr->nxt->value);
            free(curr->value);
            curr->value = tmp;
            if (curr->type == _LTRAL || curr->nxt->type == _LTRAL)
                curr->type = _LTRAL;
            else
                curr->type = _WORD;
            delete_node(curr->nxt);
        }
        else 
            curr = curr->nxt;
    }
    // remove_token(list, W_SPACE);
}


int ms_parse(t_data **data, char *line, t_env *env)
{
    t_list *list;
    t_list *last;
    int count;
    int *fds;

    count  = 0;
    fds = NULL;
    list = ms_tokenize(line);
    if (!list)
        return -1;
    if (handle_quote(&list, S_QUOTE) % 2 != 0)
    {
        expand_all(&list, env);
        return printf("quote>\n"), -1;
    }
    printf("after quotes\n");
    print_list(list);
    expand_all(&list, env);
    printf("after expand\n");
    print_list(list);
    concat_words(&list);
    printf("after concat\n");
    print_list(list);
    remove_token(&list, W_SPACE);
    if (check_syntax(&list, &count) == 1)
        return remove_list(&list), -1;
    if(count)
        fds = handle_redirections(&list, &count); 
    remove_token(&list, _RM);
    if (list->nxt)
    {
        list = list->nxt;
        list->first = 1;
        remove_token(&list->prv, NULL_TOKEN); 
    }
    handle_args(&list);
    remove_token(&list, _PIPE);
    while(fds && fds[--count])
        printf("fd : %d\n", fds[count]);
    last = get_last_node(list);
    last->last = 1;
    (*data)->cmd = list;
    (*data)->fds = fds;
    (*data)->status = 0;
    return 0;
}

//  printf("--\n");
//             if (curr->nxt)
//                 printf("curr nxt -%s- type: %d\n", curr->nxt->value, curr->nxt->type);
//             if (curr->prv)
//                 printf("curr prv -%s- type: %d\n", curr->prv->value, curr->prv->type);