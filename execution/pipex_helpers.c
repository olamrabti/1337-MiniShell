/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/29 01:35:22 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void execute_command(t_list *temp, t_data *data, char **envp)
{
	DIR *mydir;
	char *new_cmd;

	if (ft_is_builtin(temp->value))
	{
		ft_execute_builtin(temp, data);
		exit(ft_exit_status(-1));
	}
	else
	{
		if (temp->type != NULL_TOKEN)
		{
			if (ft_is_point(temp->value))
			{
				ft_putstr_fd("minishell: .: filename argument required\n", 2);
				ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
				exit(2);
			}
			if (temp->value[0] == '.' || temp->value[0] == '/')
			{
				mydir = opendir(temp->value);
				if (!mydir)
				{
					if (temp->value[ft_strlen(temp->value) - 1] == '/')
					{
						new_cmd = gc_substr(temp->value, 0, ft_strlen(temp->value) - 1, &data->addr);
						if (access(new_cmd, F_OK) == 0)
						{
							ft_putstr_fd("minishell: ", 2);
							ft_putstr_fd(temp->value, 2);
							ft_putstr_fd(": Not a directory\n", 2);
							exit(126);
						}
						else
						{
							ft_putstr_fd("minishell: ", 2);
							ft_putstr_fd(temp->value, 2);
							ft_putstr_fd(": No such file or directory\n", 2);
							exit(127);
						}
					}
				}
				if (mydir)
				{
					closedir(mydir);
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putstr_fd(": is a directory\n", 2);
					exit(126);
				}
				if (access(temp->value, X_OK) == -1 && access(temp->value, F_OK) == 0 && temp->value[0] == '.' && temp->value[1] == '/')
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putstr_fd(": Permission denied\n", 2);
					exit(126);
				}
				if (access(temp->value, X_OK) == -1 && access(temp->value, F_OK) == -1 && temp->value[0] == '.' && temp->value[1] == '/')
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					exit(127);
				}
			}
			if (ft_execute(temp, data, envp) == -1)
			{
				ft_print_error_execute_command(temp->value);
				exit(127);
			}
		}
		else
			exit(SUCCESS);
	}
}

void ft_handle_childs(t_list *temp, t_data *data, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_file_descriptors(temp);
	handle_pipes(data, temp);
	execute_command(temp, data, envp);
}

void handle_parent_pipes(t_data *data, t_list *temp)
{
	if (!temp->first)
		close(data->save);
	if (!temp->last)
	{
		close(data->pd[1]);
		data->save = dup(data->pd[0]);
		close(data->pd[0]);
	}
}

void handle_pipes(t_data *data, t_list *temp)
{
	if (!temp->first)
	{
		if (dup2(data->save, temp->infile) == -1)
			exit(-1);
		close(data->save);
	}
	if (!temp->last)
	{
		if (dup2(data->pd[1], temp->outfile) == -1)
			exit(-1);
		close(data->pd[0]);
		close(data->pd[1]);
	}
}
