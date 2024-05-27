/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/26 22:08:34 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_concat_env(char *str, t_env *envp, t_data *data)
{
	t_env	*env;
	int		start;

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

int	ft_change_env(char *str, t_env *envp, int concat, t_data *data)
{
	t_env	*env;
	int		start;
	int		len;

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
				env->value = gc_substr(str, start + 1, len - start - 1,
						&data->addr_env);
				return (SUCCESS);
			}
			env = env->next;
		}
	}
	return (SUCCESS);
}

void	ft_concat_export(char *str, t_env **env, t_addr **addr_env)
{
	char	*value;
	char	*key;
	int		start;
	int		len;

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

int	ft_process_arguments(t_list *cmd, t_env **env, t_data *data)
{
	int	flag;
	int	i;

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

int	ft_export(t_list *cmd, t_env **envp, t_data *data)
{
	int	flag;

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
