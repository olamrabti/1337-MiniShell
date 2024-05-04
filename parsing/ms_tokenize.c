/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:14:27 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/04 13:51:36 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

int ft_isprint(int c)
{
    if (c >= 32 && c < 127)
        return (1);
    return (0);
}

int ft_isdigit(int d)
{
    if (d >= '0' && d <= '9')
        return (1);
    return (0);
}
int ft_isspace(int d)
{
    if (d == ' ' || (d >= 9 && d <= 13))
        return (1);
    return (0);
}
int ft_isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int ft_isalnum(int c)
{
    if (ft_isalpha(c) || ft_isdigit(c))
        return (1);
    return (0);
}


t_list *ms_tokenize(char *line, char **envp)
{
    (void)envp;
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
        if (line[i] == '<' && line[i + 1] == '<')
        {
            node_addback(&current, create_node(ft_strdup("<<"), H_DOC));
            i++;
        }
        else if (line[i] == '>' && line[i + 1] == '>')
        {
            node_addback(&current, create_node(ft_strdup(">>"), RED_OUT_APPEND));
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
            j = get_key(&line[i], i, j);
            node_addback(&current, create_node(ft_strndup(&line[i], j), _DOLLAR));
            i += j - 1;
        }
        else if (ft_isspace(line[i]))
        {
            j = 1;
            while ((line[i + j]) && ft_isspace(line[i + j]))
                j++;
            node_addback(&current, create_node(ft_strndup(&line[i], j), W_SPACE));
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
