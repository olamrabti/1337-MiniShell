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

#include "parse.h"

char *ft_getvalue(char *key, char **envp)
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
    value = ft_getvalue(key, envp);
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
    char *tmp;

    head = create_node(NULL, NULL_TOKEN);
    current = head;
    i = 0;
    tmp = NULL;
    while (line[i])
    {
        if (line[i]== '<' && line[i + 1] == '<')
        {
            node_addback(&current, create_node(ft_strdup("<<"), H_DOC_TRUNC));
            i++;
        }
        else if (line[i] == '>' && line[i + 1] == '>')
        {
           node_addback(&current, create_node(ft_strdup(">>"), H_DOC_APPEND));
           i++;
        }
        else if (line[i] == '>')
            node_addback(&current, create_node(ft_strdup(">"), RED_OUT));
        else if (line[i] == '<')
            node_addback(&current, create_node(ft_strdup("<"), RED_IN));
        else if (line[i] == '|')
            node_addback(&current, create_node(ft_strdup("|"), _PIPE));
        else if (line[i] == '"')
            node_addback(&current, create_node(ft_strdup("\""), D_QUOTE));
        else if (line[i] == '\'')
            node_addback(&current, create_node(ft_strdup("'"), S_QUOTE));
        else if (line[i] == '$')
        {
            tmp = ft_expand_dollar(&line[i], envp);
            node_addback(&current, create_node(tmp, _DOLLAR));
            i += ft_strlen(tmp) - 1;
            free(tmp);
        }
        else
        {
            current = get_last_node(current);
            if (current && current->type == _WORD)
            current->value = ft_charjoin(current->value, line[i]);
            else
                node_addback(&current, create_node(ft_charjoin(NULL, line[i]), _WORD));
        }
        i++;
    }
    return (head);
}