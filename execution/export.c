/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/02 17:52:13 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ] var with no value
// [ ] var with value
// [ ] var already exist
// [ ] var with += value
// [ ] var with += value already exist
// [ ] var key="" empty value
// [ ] var key=" " empty value

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
            printf("=\"%s\"\n", env->value);
        env = env->next;
    }
}
static int ft_is_exist(char *str, t_env *envp)
{
    t_env *env;
    int len;

    env = envp;
    len = ft_strlen(str);
    while (env)
    {
        if ((ft_strncmp(str, env->key, len) == 0) && env->key[len] == '\0')
            return (1);
        env = env->next;
    }
    return (0);
}

int ft_change_env(char * str, t_env *envp)
{
    t_env *env;

    env = envp;
    int start = 0;
    while (str[start] != '=')
        start++;
    int len = ft_strlen(str);
    while (env)
    {
        if ((ft_strncmp(str, env->key, len) == 0))
            env->value = ft_substr(str, start, len - start);
        env = env->next;
    }
    return(SUCCESS);
}




int ft_add_to_export(char *str, t_env **env)
{
    char *key;
    char *value;

    int start = 0;
    int len = ft_strlen(str);
    printf("(len)---> %d\n", len);
    while ((str[start]) && (str[start] != '='))
        start++;
    printf("(start)---> %d\n", start);
    if (start == len)
        value = NULL;
    else
    {
        value = ft_substr(str, start + 1, len - start);
        printf("(value) ---> %s\n", value);
    }
    key = ft_substr(str, 0, start);
    printf("(key)---> %s\n", key);
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
            if (ft_is_exist(cmd->args[i], *env))
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
