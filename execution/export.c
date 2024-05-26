/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/26 16:19:56 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

t_env *ft_sort_export(t_env **envp)
{
    t_env *env;
    t_env *temp;
    char *swap_key;
    char *swap_value;

    env = *envp;
    while (env)
    {
        temp = env->next;
        while (temp)
        {
            if (ft_strcmp(temp->key, env->key) < 0)
            {
                swap_key = temp->key;
                temp->key = env->key;
                env->key = swap_key;
                swap_value = temp->value;
                temp->value = env->value;
                env->value = swap_value;
            }
            temp = temp->next;
        }
        env = env->next;
    }
    return *envp;
}

void ft_print_export(t_env **envp, int flag)
{
    t_env *env;

    env = ft_sort_export(envp);
    while (env)
    {
        if (ft_strcmp(env->key, "PATH") == 0 && flag == 1)
        {
            env = env->next;
            continue;
        }
        printf("declare -x ");
        printf("%s", env->key);
        if (env->value)
            printf("=\"%s\"", env->value);
        printf("\n");
        env = env->next;
    }
}

int ft_is_exist_concat(char *str, t_env *envp)
{
    t_env *env;
    int start;

    start = 0;
    env = envp;
    while (str[start] && (str[start] != '+'))
        start++;
    while (env)
    {
        if ((ft_strncmp(str, env->key, start) == 0) && (env->key[start] == '\0'))
            return (1);
        env = env->next;
    }
    return (0);
}

int ft_is_exist(char *str, t_env *envp, int concat)
{
    t_env *env;
    int start;

    env = envp;
    start = 0;
    if (concat)
        return (ft_is_exist_concat(str, envp));
    else
    {
        while (str[start] && (str[start] != '='))
            start++;
        while (env)
        {
            if ((ft_strncmp(str, env->key, start) == 0) && (env->key[start] == '\0'))
                return (1);
            env = env->next;
        }
    }
    return (0);
}

char *ft_strjoin_export(char *s1, char *s2, t_data *data)
{
    int i;
    char *result;

    i = 0;
    if (!s2)
        return (NULL);
    if (!s1)
        s1 = gc_strdup("", &data->addr_env);
    result = (char *)ft_calloc(&data->addr_env, ((ft_strlen(s2) + ft_strlen(s1)) + 1), sizeof(char));
    if (!result)
        return (0);
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i])
    {
        result[ft_strlen(s1) + i] = s2[i];
        i++;
    }
    result[i + ft_strlen(s1)] = '\0';
    return (result);
}

int ft_concat_env(char *str, t_env *envp, t_data *data)
{
    t_env *env;
    int start;

    env = envp;
    start = 0;
    while (str[start] && str[start] != '+')
        start++;
    while (env)
    {
        if (ft_strncmp(str, env->key, start) == 0)
        {
            env->value = ft_strjoin_export(env->value, str + (start + 2), data);
            return (SUCCESS);
        }
        env = env->next;
    }
    return (SUCCESS);
}

int ft_change_env(char *str, t_env *envp, int concat, t_data *data)
{
    t_env *env;
    int start;
    int len;

    env = envp;
    start = 0;
    len = ft_strlen(str);
    if (concat)
        return (ft_concat_env(str, env, data));
    else
    {
        while (str[start] && str[start] != '=')
            start++;
        while (env)
        {
            if ((ft_strncmp(str, env->key, start) == 0) && ((len - start) != 0))
            {
                env->value = gc_substr(str, start + 1, len - start - 1, &data->addr);
                return (SUCCESS);
            }
            env = env->next;
        }
    }
    return (SUCCESS);
}

void ft_concat_export(char *str, t_env **env, t_addr **addr_env)
{
    int start;
    int len;
    char *key;
    char *value;

    len = ft_strlen(str);
    start = 0;
    while ((str[start]) && (str[start] != '+'))
        start++;
    if (start == len)
        value = NULL;
    else
        value = gc_strjoin("", str + (start + 2), addr_env);
    key = gc_substr(str, 0, start, addr_env);
    ft_add_to_env(env, key, value, addr_env);
}

int ft_add_to_export(char *str, t_env **env, int concat, t_addr **addr_env)
{
    char *key;
    char *value;
    int start;

    start = 0;
    int len;
    len = ft_strlen(str);
    if (concat)
        ft_concat_export(str, env, addr_env);
    else
    {
        while ((str[start]) && (str[start] != '='))
            start++;
        if (start == len)
            value = NULL;
        else
            value = gc_substr(str, start + 1, len - start, addr_env);
        key = gc_substr(str, 0, start, addr_env);
        ft_add_to_env(env, key, value, addr_env);
    }
    return (SUCCESS);
}

int ft_is_concat(char *str)
{
    int i = 0;

    while (str[i] && str[i] != '=')
    {
        if (str[i] == '+' && str[i + 1] == '=')
            return (1);
        i++;
    }
    return (0);
}

int ft_export_is_valid(char *str)
{
    int i;

    i = 0;
    if (ft_isalpha(str[0]) || str[0] == '_')
    {
        i++;
        while (str[i] && (str[i] != '=' && str[i] != '+'))
        {
            if (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            else
                return (0);
        }
    }
    else
        return (0);
    return (1);
}

int ft_double_check(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '+')
        {
            i++;
            if (str[i] == '=')
                return 1;
            return 0;
        }
        i++;
    }
    return 1;
}

int handle_export_argument(char *arg, t_env **env, t_data *data)
{
    int concat;

    concat = ft_is_concat(arg);
    if ((ft_strncmp(arg, "PATH", 4) == 0) && (arg[4] == '=' || arg[4] == '+'))
        data->is_hiden = 0;
    if (ft_is_exist(arg, *env, concat))
        ft_change_env(arg, *env, concat, data);
    else
        ft_add_to_export(arg, env, concat, &data->addr_env);
    return (SUCCESS);
}

int ft_process_arguments(t_list *cmd, t_env **env, t_data *data)
{
    int flag;
    int i;

    flag = 0;
    i = 0;
    while (cmd->args[i])
    {
        if (ft_export_is_valid(cmd->args[i]) && ft_double_check(cmd->args[i]))
            handle_export_argument(cmd->args[i], env, data);
        else
        {
            flag = 1;
            ft_putstr_fd("export: ", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd(": not a valid identifier\n", 2);
        }
        i++;
    }
    return (flag);
}

int ft_export(t_list *cmd, t_env **envp, t_data *data)
{
    int flag;

    if (cmd->args)
    {
        flag = ft_process_arguments(cmd, envp, data);
        if (flag)
            return (ERROR);
        else
            return (SUCCESS);
    }
    else
    {
        ft_print_export(envp, data->is_hiden);
        return (SUCCESS);
    }
}
