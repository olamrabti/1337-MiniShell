/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:30 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/23 10:56:48 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void ft_add_to_env(t_env **env, char *key, char *value)
{
    t_env *new_env;
    t_env *temp;

    new_env = malloc(sizeof(t_env));
    if (!new_env)
        return;
    new_env->key = key;
    new_env->value = value;
    new_env->next = NULL;
    if (*env == NULL)
    {
        *env = new_env;
        return;
    }
    temp = *env;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_env;
}

void ft_fill_path(t_env *env)
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (ft_strncmp(temp->key, "PATH", 4) == 0)
            temp->path = ft_split(temp->value, ':');
        temp = temp->next;
    }
}

t_env *ft_parce_env(char **envp)
{
    t_env *env;
    char *value;
    char *key;
    int i;
    int j;

    i = 0;
    env = malloc(sizeof(t_env *));
    if (!env)
        return (NULL);
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] != '=')
            j++;
        key = ft_substr(envp[i], 0, j);
        value = ft_substr(envp[i], j + 1 , ft_strlen(envp[i]) - j - 1);
        ft_add_to_env(env, key, value);
        i++;
    }
    ft_fill_path(env);
    return (env);
}

