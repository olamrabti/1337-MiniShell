/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:14:27 by olamrabt          #+#    #+#             */
/*   Updated: 2024/03/04 15:37:12 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *ft_getenv(char *key, char **envp)
{
    int i;
    int j;
    
    i = 0;
    while (envp[i])
    {
        if(ft_strcmp(key, envp[i]) == 0)
        {
            j = 0;
            while (envp[i][j] != '=')
                j++;
            return (ft_strdup(&envp[i][j + 1]));
        }
        i++;
    }
    return (NULL);
}

char *ft_expand_dollar(char *line, char **envp)
{
    int i;
    char *value;
    char *key;
    char *tmp;
    i = 0;
    while (line[i] && line[i] != ' ')
        i++;
    key = ft_strndup(line, i);
    value = ft_getenv(key, envp);
    if (value == NULL)
        return (NULL);
    tmp = ft_strdup(value);
    free(key);
    free(value);
    return (tmp);
}

t_list *ms_tokenize(char *line, char **envp)
{
    t_list *head;
    t_list *current;
    int i;

    head = malloc(sizeof(t_list));
    head->value = NULL;
    head->type = NULL_TOKEN;
    head->prv = NULL;
    head->nxt = NULL;
    current = head;
    i = 0;
    while (line[i])
    {
        if (line[i] == '>')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = RED_OUT;
            current->nxt = NULL;
        }
        else if (line[i] == '<')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = RED_IN;
            current->nxt = NULL;
        }
        else if (line[i] == '|')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = _PIPE;
            current->nxt = NULL;
        }
        else if (line[i] == '$')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = _DOLLAR;
            current->nxt = NULL;
        }
        else if (line[i] == '"')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = D_QUOTE;
            current->nxt = NULL;
        }
        else if (line[i] == '\'')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = S_QUOTE;
            current->nxt = NULL;
        }
        else if (line[i]== '<<')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = H_DOC_TRUNC;
            current->nxt = NULL;
        }
        else if (line[i] == '>>')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = NULL;
            current->type = H_DOC_APPEND;
            current->nxt = NULL;
        }
        else if (line[i]== '$')
        {
            current->nxt = malloc(sizeof(t_list));
            current->nxt->prv = current;
            current = current->nxt;
            current->value = ft_expand_dollar(&line[i], envp);
            current->type = _DOLLAR;
            current->nxt = NULL;
            
        }
        else if (line[i] == ' ')
        {
            if (current->value != NULL)
            {
                current->nxt = malloc(sizeof(t_list));
                current->nxt->prv = current;
                current = current->nxt;
                current->value = NULL;
                current->type = _SPACE;
                current->nxt = NULL;
            }
        }
        else
        {
            if (current->value == NULL)
                current->value = ft_strdup(&line[i]);
            else
                current->value = ft_strjoin(current->value, &line[i]);
        }
        i++;
    }
    return (head);
}