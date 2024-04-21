/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/21 15:41:51 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// [ ] OLDENV
// [ ] update env in the case of inset 

char *ft_strdup(char *str)
{
    int i;
    char *p;

    i = 0;
    p = (char *)malloc(ft_strlen(str) + 1 * sizeof(char));
    if (p == NULL)
        return (NULL);
    while (str[i] != '\0')
    {
        p[i] = str[i];
        i++;
    }
    p[i] = '\0';
    return (p);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    char *byte_dest;
    char *byte_src;

    if (!src && !dest)
        return (NULL);
    if (src == dest)
        return (dest);
    i = 0;
    byte_dest = (char *)dest;
    byte_src = (char *)src;
    while (i < n)
    {
        byte_dest[i] = byte_src[i];
        i++;
    }
    return (byte_dest);
}

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char *result;

    if (!s)
        return (NULL);
    if (start >= (unsigned int)ft_strlen(s) || !len)
        return (ft_strdup(""));
    if (len + start > (unsigned int)ft_strlen(s))
        len = (unsigned int)ft_strlen(s) - start;
    result = (char *)malloc((len + 1) * sizeof(char));
    if (!result)
        return (NULL);
    ft_memcpy(result, s + start, len);
    result[len] = '\0';
    return (result);
}

void ft_add_env(t_env **env, char *key, char *value)
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

void ft_parce_env(char **envp, t_env **env)
{
    int i;
    int j;
    char *key;
    char *value;

    i = 0;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] != '=')
            j++;
        key = ft_substr(envp[i], 0, j);
        value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
        ft_add_env(env, key, value);
        i++;
    }
}

void ft_env(char **envp)
{
    t_env *env;

    env = NULL;
    ft_parce_env(envp, &env);
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

void ft_fill_env(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        if (ft_strcmp(env->key, "PATH") == 0)
        {
            env->env = ft_strdup(env->value);
        }
        env = env->next;
    }
}

int main(int argc, char *argv[], char *env[])
{
    ft_env(env);
    return 0;
}
