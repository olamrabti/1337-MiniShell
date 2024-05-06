/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/05 18:26:17 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [x] var with no value
// [x] var with value
// [x] var already exist
// [x] var with += value
// [x] var with += value already exist
// [x] var key="" empty value
// [x] var key=" " empty value
// [x] invalid var

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
static int ft_is_exist(char *str, t_env *envp, int concat)
{
    t_env *env;

    env = envp;
    int start = 0;
    if (concat)
    {
        while (str[start] && (str[start] != '+'))
            start++;
        while (env)
        {
            if ((ft_strncmp(str, env->key, start) == 0) && (env->key[start] == '\0'))
                return (1);
            env = env->next;
        }
    }
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

char	*ft_strjoin_export(char *s1, char *s2)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	if (!s2)
		return (NULL);
    if (!s1)
        s1 = ft_strdup("");
	len = ft_strlen(s2) + ft_strlen(s1);
	result = (char *)malloc((len + 1) * sizeof(char));
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

int ft_change_env(char *str, t_env *envp, int concat)
{
    t_env *env = envp;
    int start = 0;

    int len = ft_strlen(str);
    if (concat)
    {
        while (str[start] && str[start] != '+')
            start++;
        while (env)
        {
            if (ft_strncmp(str, env->key, start) == 0)
            {
                // env->value = ft_substr(str, start + 1, len - start - 1);
                env->value = ft_strjoin_export(env->value, str + (start + 2));
                return (SUCCESS);
            }
            env = env->next;
        }
    }
    else
    {
        while (str[start] && str[start] != '=')
            start++;

        while (env)
        {
            // printf("len li khas y talloca %d\n", len - start);
            if ((ft_strncmp(str, env->key, start) == 0) && ((len - start) != 0))
            {
                env->value = ft_substr(str, start + 1, len - start - 1);
                return (SUCCESS);
            }
            env = env->next;
        }
    }
    return (SUCCESS);
}

int ft_add_to_export(char *str, t_env **env, int concat)
{
    char *key;
    char *value;

    int start = 0;
    int len = ft_strlen(str);
    if (concat)
    {
        while ((str[start]) && (str[start] != '+'))
            start++;
        if (start == len)
            value = NULL;
        else
        {
            // value = ft_substr(str, start + 1, len - start);
            value = ft_strjoin("", str + (start + 2));
        }
        key = ft_substr(str, 0, start);
        ft_add_to_env(env, key, value);
    }
    else
    {
        while ((str[start]) && (str[start] != '='))
            start++;
        if (start == len)
            value = NULL;
        else
            value = ft_substr(str, start + 1, len - start);
        key = ft_substr(str, 0, start);
        ft_add_to_env(env, key, value);
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
    int i = 0;
    if (ft_isalpha(str[0]) || str[0] == '_')
    {
        i++;
        while (str[i] && (str[i] != '=' && str[i] != '+'))
        {
            if (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            else
                return 0;
        }
    }
    else
        return (0);
    return (1);
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
            if (ft_export_is_valid(cmd->args[i]))
            {
                int concat = ft_is_concat(cmd->args[i]);
                printf("concat --> %d\n", concat);
                if (ft_is_exist(cmd->args[i], *env, concat) == 1)
                {
                    // [ ] change its value
                    ft_change_env(cmd->args[i], *env, concat);
                }
                else
                {
                    // [ ] add node and if there is '=' assigne a value
                    ft_add_to_export(cmd->args[i], env, concat);
                }
            }
            else
            {
                ft_putstr_fd("export: ", 2);
                ft_putstr_fd(cmd->args[i], 2);
                ft_putstr_fd(": not a valid identifier\n", 2);
            }
            // move to next argument
            i++;
        }
    }
    else
        ft_print_export(*env);

    return (SUCCESS);
}
