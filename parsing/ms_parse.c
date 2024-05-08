/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:04:22 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/08 14:08:51 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

void ft_join_q(char *tmp, t_list *curr, t_addr **addr)
{
    if (curr && curr->prv && curr->prv->type == WORD)
    {
        tmp = ft_strjoin(curr->prv->value, curr->value, addr);
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
        if (temp)
            temp = temp->nxt;
    }
}


int check_syntax(t_list **list, int *count)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr->type == PIPE)
        {
            if ((!curr->prv || curr->prv->type != WORD) || (!curr->nxt || curr->nxt->type != WORD))
                return printf("invalid PIPE syntax\n"), 1;
        }
        if (curr->type == RED_IN || curr->type == RED_OUT || curr->type == RED_OUT_APPEND)
        {
            (*count)++;
            if (curr->nxt && curr->nxt->type == NF_VAR)
                return printf("ambiguous redirect\n"), 1;
            if ((!curr->nxt || curr->nxt->type != WORD))
                return printf("invalid RED or H_DOC_APP syntax\n"), 1;
        }
        if (curr->type == H_DOC)
        {
            (*count)++;
            if ((!curr->nxt))
                return printf("syntax error near unexpected token `newline'\n"), 1;
            if ((curr->nxt && curr->nxt->type != WORD && curr->nxt->type != LTRAL))
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
        curr->type = RM;
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
        while (curr && (curr->type == WORD || curr->type == LTRAL) 
            && curr->nxt && (curr->nxt->type == WORD || curr->nxt->type == LTRAL))
        {
            count++;
            curr = curr->nxt;
        }
        if (curr && count > 1 && fill_args(curr, count))
            printf("parsing : filling args failed\n");
        if (curr)
            curr = curr->nxt;
    }
    remove_token(list, RM);
}

void concat_words(t_list **list, t_addr **addr)
{
    t_list *curr;
    char *tmp;

    curr = *list;
    while (curr)
    {
        if ((curr->type == WORD || curr->type == NF_VAR || curr->type == LTRAL) 
        && curr->nxt && (curr->nxt->type == WORD || curr->nxt->type == NF_VAR || curr->nxt->type == LTRAL))
        {
            tmp = ft_strjoin(curr->value, curr->nxt->value, addr);
            // free(curr->value);
            curr->value = tmp;
            if (curr->type == LTRAL || curr->nxt->type == LTRAL)
                curr->type = LTRAL;
            else
                curr->type = WORD;
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

    count = 0;
    fds = NULL;
    list = ms_tokenize(line, &((*data)->addr));
    // printf("after tokenzing\n");
    // print_list(list);
    if (!list)
        return -1;
    if (handle_quote(&list, S_QUOTE, &((*data)->addr)) % 2 != 0)
    {
        expand_all(&list, env, &((*data)->addr));
        printf("quote>\n");
    }
    // printf("after quotes\n");
    // print_list(list);
    expand_all(&list, env, &((*data)->addr));
    // printf("after expand\n");
    // print_list(list);
    concat_words(&list, &((*data)->addr));
    // printf("after concat\n");
    // print_list(list);
    remove_token(&list, W_SPACE);
    if(!check_syntax(&list, &count) && count)
        fds = handle_redirections(&list, &count, &((*data)->addr)); 
    remove_token(&list, RM);
    if (list->nxt)
    {
        list = list->nxt;
        list->first = 1;
        remove_token(&list->prv, NULL_TOKEN);
    }
    handle_args(&list);
    remove_token(&list, PIPE);
    while(fds && fds[--count])
        printf("fd : %d\n", fds[count]);
    last = get_last_node(list);
    last->last = 1;
    (*data)->cmd = list;
    (*data)->fds = fds;
    (*data)->status = 0;
    // printf("final ------> \n");
    // print_list(list);
    return 0;
}

//  printf("--\n");
//             if (curr->nxt)
//                 printf("curr nxt -%s- type: %d\n", curr->nxt->value, curr->nxt->type);
//             if (curr->prv)
//                 printf("curr prv -%s- type: %d\n", curr->prv->value, curr->prv->type);