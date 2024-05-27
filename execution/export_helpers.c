/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:03:23 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/26 22:15:36 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_double_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_is_valid(char *str)
{
	int	i;

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

int	ft_is_concat(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_exist_concat(char *str, t_env *envp)
{
	t_env	*env;
	int		start;

	start = 0;
	env = envp;
	while (str[start] && (str[start] != '+'))
		start++;
	while (env)
	{
		if ((ft_strncmp(str, env->key, start) == 0)
			&& (env->key[start] == '\0'))
			return (1);
		env = env->next;
	}
	return (0);
}

int	ft_is_exist(char *str, t_env *envp, int concat)
{
	t_env	*env;
	int		start;

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
			if ((ft_strncmp(str, env->key, start) == 0)
				&& (env->key[start] == '\0'))
				return (1);
			env = env->next;
		}
	}
	return (0);
}
