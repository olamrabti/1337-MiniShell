/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:14:27 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/01 12:24:16 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"


int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

int	ft_isdigit(int d)
{
	if (d >= '0' && d <= '9')
		return (1);
	return (0);
}
int	ft_isspace(int d)
{
	if (d == ' ' || (d >= 9 && d <= 13))
		return (1);
	return (0);
}
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

char *ft_getvalue(char *key, char **envp)
{
    int i;
    int j;
    
    i = 0;
    while (envp[i])
    {
        if(ft_strncmp(key, envp[i], ft_strlen(key)) == 0)
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

char *ft_expand(char *key, char **envp)
{
    char *value;
    
    if (ft_strncmp(key, "$_", ft_strlen(key)) == 0)
        return key;
    if (ft_strncmp(key, "$$", ft_strlen(key)) == 0)
        return key;
    // if (ft_strncmp(key, "$?", ft_strlen(key)) == 0)
    //     return strdup : ft_itoa(exitstatus);
    if (key && (ft_strlen(key) == 1 || ft_isdigit(key[1])))
        return (ft_strdup(""));
    value = ft_getvalue(key + 1, envp);
    // remmember to free it before give it the new strdup value
    if (!value)
        return (ft_strdup(""));
    // if (!value)
    //     return (ft_strdup(key + 1));
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
            j = 1;
            // maybe add '_' because it's valid and dont expand it.
            while ((line[i + j]) 
                && (ft_isalnum(line[i + j]) || line[i + j] == '$' || line[i + j] == '_' || line[i + j] == '?'))
            {
                j++;
                if (j == 2 && (line[i + j - 1] == '$' || line[i + j - 1] == '?'))
                    break;
                else if (j == 2 && ft_isdigit(line[i + j - 1]))
                    break;
                else if (j > 2 && line[i + j - 1] == '$')
                {
                    j--;
                    break;
                }
            }
            node_addback(&current, create_node(ft_strndup(&line[i], j), _DOLLAR));
            i += j - 1;
        }
        else if (ft_isspace(line[i]))
        {
            j = 1;
            while ((line [i + j]) && ft_isspace(line[i + j]))
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
