/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:46:17 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/04 14:18:09 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

char *ft_getvalue(char *key, char **envp)
{
    int i;
    int j;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0)
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
int get_key(char *line, int i, int j)
{
    j = 1;
    while ((line[i + j]) && (ft_isalnum(line[i + j]) || line[i + j] == '$' || line[i + j] == '_' || line[i + j] == '?'))
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
    return j;
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

void expand_all(t_list **list, char **envp)
{
    t_list *curr;
    char *tmp;

    curr = *list;
    while (curr)
    {
        if (curr->prv && curr->prv->type == H_DOC)
        {
            if (curr->type != _LTRAL)
                curr->type = _WORD;
            curr = curr->nxt;
        }
        else if (curr->type == _DOLLAR)
        {
            tmp = ft_expand(curr->value, envp);
            // free(curr->value); // it crashes the code 
            curr->value = tmp;
            if (*tmp)
                curr->type = _WORD;
            else
                curr->type = NF_VAR;
        }
        if(curr)
            curr = curr->nxt;
    }
}