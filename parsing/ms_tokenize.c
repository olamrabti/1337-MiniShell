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
    printf("key: -%s-\n", key);
    while (envp[i])
    {
        if(ft_strncmp(key, envp[i], ft_strlen(key)) == 0)
        {
            j = 0;
            while (envp[i][j] != '=')
                j++;
            return (ft_strdup(&envp[i][j + 1]));
        }
        printf("%s\n", envp[i]);
        i++;
    }
    return (NULL);
}

char *ft_expand_dollar(char *key, char **envp)
{
    char *value;
    if (key && key[1] == '\0')
        return (key);
    value = ft_getvalue(key + 1, envp);
    if (!value)
        return (key);
    return (value);
}


t_list *ms_tokenize(char *line, char **envp)
{
    (void ) envp;
    t_list *head;
    t_list *current;
    int i;
    int j;

    head = create_node(NULL, NULL_TOKEN);
    current = head;
    i = 0;
    j = 0;
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
            j = 1;
            while (line [i + j] && (line[i + j] != ' ' || line[i + j] != '"'))
                j++;
            printf("j: %d\n", j); 
            // still not fixed yet 
            node_addback(&current, create_node(ft_strndup(&line[i], j), _DOLLAR));
            i += j - 1;
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