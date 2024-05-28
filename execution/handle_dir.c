/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:19:16 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/28 23:10:34 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_is_point(char *str)
{
	if (str && *str)
	{
		if (str[0] == '.' && str[1] == '\0')
			return (1);
	}
	return (0);
}

int	ft_is_a_dir(char *str)
{
	int	i;

	if (ft_is_point(str))
		return (1);
	i = 0;
	if (str && *str)
	{
		while (str[i])
		{
			if (str[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_file_exist(t_list *cmd, t_data *data, char **envp)
{
	DIR	*dir;

	dir = opendir(cmd->value);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (ft_exit_status(126));
	}
	if (access(cmd->value, X_OK) == 0)
	{
		if (ft_execute(cmd, data, envp) == -1)
			return (ft_exit_status(126));
		return (ft_exit_status(0));
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": permission denied\n", 2);
		return (ft_exit_status(126));
	}
}

int	ft_handle_dir(t_list *cmd, t_data *data, char **envp)
{
	int	status;

	status = 0;
	if (ft_is_point(cmd->value))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (ft_exit_status(2));
	}
	else
	{
		if (access(cmd->value, F_OK) == 0)
		{
			status = ft_file_exist(cmd, data, envp);
			return (status);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (ft_exit_status(127));
		}
	}
	return (0);
}
