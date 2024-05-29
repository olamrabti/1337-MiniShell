/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:30 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/29 18:03:29 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void	ft_add_to_env(t_env **env, char *key, char *value, t_addr **addr)
{
	t_env	*new_env;
	t_env	*temp;

	if (!key)
		return ;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		exit(1);
	new_env->key = gc_strdup(key, addr);
	if (!value)
		new_env->value = NULL;
	else
		new_env->value = gc_strdup(value, addr);
	new_env->next = NULL;
	if (!*env)
	{
		*env = new_env;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
}

t_env	*ft_parce_env(char **envp, t_addr **addr_env)
{
	t_env	*env;
	char	*value;
	char	*key;
	int		i;
	int		j;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = gc_substr(envp[i], 0, j, addr_env);
		value = gc_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1, addr_env);
		ft_add_to_env(&env, key, value, addr_env);
		free(key);
		free(value);
		i++;
	}
	return (env);
}

char	*inc_shell_level(char *value, t_addr **addr_env)
{
	char	*tmp;

	tmp = value;
	value = gc_itoa(ft_atoi(value) + 1, addr_env);
	free(tmp);
	return (value);
}

char	*ft_fill_envp(t_env *env, char *envp, t_addr **addr_env)
{
	char	*value;

	value = env->value;
	if (ft_strcmp(env->key, "SHLVL") == 0)
		value = inc_shell_level(value, addr_env);
	envp = gc_strjoin(env->key, "=", addr_env);
	envp = gc_strjoin(envp, value, addr_env);
	return (envp);
}

char	**convert_envp(t_env *envp_lst, t_addr **addr_env)
{
	t_env	*env;
	size_t	size;
	char	**envp;
	int		i;

	i = 0;
	env = envp_lst;
	if (envp_lst == NULL)
		return (NULL);
	size = ft_lstsize(envp_lst);
	if (size == 0)
		return (NULL);
	envp = (char **)ft_calloc(addr_env, (size + 1), sizeof(char *));
	if (!envp)
		exit(1);
	while (env)
	{
		envp[i] = ft_fill_envp(env, envp[i], addr_env);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
