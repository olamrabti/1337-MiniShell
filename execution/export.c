/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/03 18:12:32 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [x] var with no value
// [x] var with value
// [x] var already exist
// [ ] var with += value
// [ ] var with += value already exist
// [x] var key="" empty value
// [x] var key=" " empty value


void ft_print_export(t_env *envp)
{
    t_env *env;

    env = envp;
    while (env)
    {
        printf("declare -x ");
        printf("%s", env->key);
        // potentiel segfault
        if (env->value)
            printf("=\"%s\"", env->value);
        printf("\n");
        env = env->next;
    }
}
static int ft_is_exist(char *str, t_env *envp)
{
    t_env *env;

    env = envp;
    int start = 0;
    while (str[start] && (str[start] != '='))
        start++;
    while (env)
    {
        if ((ft_strncmp(str, env->key, start) == 0) && (env->key[start] == '\0'))
            return (1);
        env = env->next;
    }
    return (0);
}

int ft_change_env(char *str, t_env *envp)
{
    t_env *env = envp;
    int start = 0;
    while (str[start] && str[start] != '=')
        start++;
    int len = ft_strlen(str);
    while (env)
    {
        if (ft_strncmp(str, env->key, start) == 0)
        {
            env->value = ft_substr(str, start + 1, len - start - 1);
            return (SUCCESS);
        }
        env = env->next;
    }
    return (SUCCESS);
}

int ft_add_to_export(char *str, t_env **env)
{
    char *key;
    char *value;

    int start = 0;
    int len = ft_strlen(str);
    while ((str[start]) && (str[start] != '='))
        start++;
    if (start == len)
        value = NULL;
    else
        value = ft_substr(str, start + 1, len - start);
    key = ft_substr(str, 0, start);
    ft_add_to_env(env, key, value);

    // free(key);
    // free(value);
    return (SUCCESS);
}

int ft_export(t_list *cmd, t_env **envp)
{
    t_env **env;
    int i;

    env = envp;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            if (ft_is_exist(cmd->args[i], *env) == 1)
            {
                // [ ] change its value
                ft_change_env(cmd->args[i], *env);
            }
            else
            {
                // [ ] add node and if there is '=' assigne a value
                ft_add_to_export(cmd->args[i], env);
            }
            // move to next argument
            i++;
        }
    }
    else
        ft_print_export(*env);

    return (SUCCESS);
}
