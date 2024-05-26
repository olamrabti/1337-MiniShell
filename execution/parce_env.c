/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:30 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/25 16:35:15 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void ft_add_to_env(t_env **env, char *key, char *value)
{
    t_env *new_env;
    t_env *temp;

    if (!key)
        return;
    new_env = malloc(sizeof(t_env));
    if (!new_env)
        exit(1);
    new_env->key = ft_strdup(key);
    if (!value)
        new_env->value = NULL;
    else
        new_env->value = ft_strdup(value);
    new_env->next = NULL;
    if (!*env)
    {
        *env = new_env;
        return;
    }
    temp = *env;
    while (temp->next)
        temp = temp->next;
    temp->next = new_env;
}

t_env *ft_parce_env(char **envp)
{
    t_env *env;
    char *value;
    char *key;
    int i;
    int j;

    env = NULL;
    i = 0;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] != '=')
            j++;
        key = ft_substr(envp[i], 0, j);
        value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
        ft_add_to_env(&env, key, value);
        free(key);
        free(value);
        i++;
    }
    return (env);
}


