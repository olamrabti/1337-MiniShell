/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/06/02 19:21:58 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void	execute_command(t_list *temp, t_data **data)
{
	if (ft_is_builtin(temp->value))
	{
		ft_execute_builtin(temp, data);
		exit(ft_exit_status(-1));
	}
	else
	{
		if (temp->type != NULL_TOKEN)
		{
			ft_handle_dir(temp, *data);
			if (ft_execute(temp, *data) == -1)
			{
				ft_print_error_execute_command(temp->value);
				exit(127);
			}
		}
		else
			exit(SUCCESS);
	}
}

void	ft_handle_childs(t_list *temp, t_data **data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_file_descriptors(temp);
	handle_pipes(*data, temp);
	execute_command(temp, data);
}

void	handle_parent_pipes(t_data *data, t_list *temp)
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

void	handle_pipes(t_data *data, t_list *temp)
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
