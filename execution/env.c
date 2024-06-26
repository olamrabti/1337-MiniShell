/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/31 15:41:08 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void	free_env_node(t_env *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
}

void	ft_print_error_env(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_print_env(t_env *envp, t_data *data)
{
	t_env	*env;

	env = envp;
	while (env)
	{
		if (env && env->key && env->value)
		{
			if (data->is_hiden == 1 && ft_strcmp(env->key, "PATH") == 0)
			{
				env = env->next;
				continue ;
			}
			if (data->oldpwd == 1 && ft_strcmp(env->key, "OLDPWD") == 0)
			{
				env = env->next;
				continue ;
			}
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
}

int	ft_env(t_list *cmd, t_env **envp, t_data *data)
{
	t_env	*env;

	ft_exit_status(0);
	env = *envp;
	if (cmd->args != NULL)
	{
		ft_print_error_env(cmd->args[0]);
		return (ERROR);
	}
	ft_print_env(env, data);
	return (SUCCESS);
}
