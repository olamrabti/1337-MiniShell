/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/31 19:03:50 by oumimoun         ###   ########.fr       */
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

int	ft_change_env(char *str, int concat, t_data **data)
{
	t_env	*env;
	int		start;
	int		len;
	char	*key;

	env = (*data)->env;
	start = 0;
	len = ft_strlen(str);
	if (concat)
		return (ft_concat_env(str, env, *data));
	else
	{
		while (str[start] && str[start] != '=')
			start++;
		key = gc_substr(str,0,start, &(*data)->addr_env);
		while (env)
		{
			if ((ft_strcmp(key, env->key) == 0))
			{
			env->value = gc_substr(str, start + 1, len - start - 1,
						&(*data)->addr_env);
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

void	ft_process_arguments(t_list *cmd, t_data **data)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_export_is_valid(cmd->args[i]) && ft_double_check(cmd->args[i]))
		{
			puts("in");
			handle_export_argument(cmd->args[i], data);
		}
		else
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			ft_exit_status(1);
		}
		i++;
	}
}

int	ft_export(t_list *cmd, t_data **data)
{
	ft_exit_status(0);
	if (cmd->args)
	{
		ft_process_arguments(cmd, data);
		return (ft_exit_status(-1));
	}
	else
	{
		ft_print_export(data, (*data)->is_hiden);
		return (SUCCESS);
	}
}
