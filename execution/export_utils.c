/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:58:29 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/31 18:46:24 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

t_env	*ft_sort_export(t_env **envp)
{
	t_env	*env;
	t_env	*temp;
	char	*swap_key;
	char	*swap_value;

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
	return (*envp);
}

void	ft_print_export(t_data **data, int flag)
{
	t_env	*env;

	env = ft_sort_export(&(*data)->env);
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0 && flag == 1)
		{
			env = env->next;
			continue ;
		}
		printf("declare -x ");
		printf("%s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

char	*ft_strjoin_export(char *s1, char *s2, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		s1 = gc_strdup("", &data->addr_env);
	result = (char *)ft_calloc(&data->addr_env,
			((ft_strlen(s2) + ft_strlen(s1)) + 1), sizeof(char));
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

int	handle_export_argument(char *arg, t_data **data)
{
	int	concat;
	t_env *env;

	env = (*data)->env;
	concat = ft_is_concat(arg);
	printf("concat=[%d]\n", concat);
	if ((ft_strncmp(arg, "PATH", 4) == 0) && (arg[4] == '=' || arg[4] == '+'))
		(*data)->is_hiden = 0;
	if (ft_is_exist(arg, (*data)->env, concat))
	{
		puts("ft_change_env");
		ft_change_env(arg, concat, data);
		// printf("%p\n", (*data)->env);
		// while (env)
		// {
		// 	printf("|%s|=|%s|\n", env->key, env->value);
		// 	env = env->next;
		// }
		
		
	}
	else
	{
		puts("ft_add_to_export");
		ft_add_to_export(arg, &(*data)->env, concat, &(*data)->addr_env);
	}
	return (SUCCESS);
}

int	ft_add_to_export(char *str, t_env **env, int concat, t_addr **addr_env)
{
	char	*key;
	char	*value;
	int		len;
	int		start;

	start = 0;
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
