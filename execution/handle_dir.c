/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:19:16 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/31 14:36:15 by oumimoun         ###   ########.fr       */
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

void	ft_open_dir(t_list *temp, t_data *data)
{
	DIR	*mydir;

	mydir = opendir(temp->value);
	if (!mydir)
		ft_not_a_dir(temp, data);
	if (mydir)
	{
		closedir(mydir);
		if ((temp->value[0] == '.' && temp->value[1] == '/') || temp->value[0] == '/')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp->value, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	ft_permission_denied(t_list *temp)
{
	if (access(temp->value, X_OK) == -1 && access(temp->value, F_OK) == 0 \
		&& temp->value[0] == '.' && temp->value[1] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (access(temp->value, X_OK) == -1 && access(temp->value, F_OK) == -1 \
		&& temp->value[0] == '.' && temp->value[1] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	ft_handle_dir(t_list *temp, t_data *data)
{
	if (ft_is_point(temp->value))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		exit(2);
	}
	if (ft_strcmp(temp->value, "..") == 0)
	{
		if (ft_execute(temp, data) == -1)
		{
			ft_print_error_execute_command(temp->value);
			exit(127);
		}
	}
	ft_open_dir(temp, data);
	ft_permission_denied(temp);
}
