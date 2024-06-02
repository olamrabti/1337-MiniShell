/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:02 by oumimoun          #+#    #+#             */
/*   Updated: 2024/06/03 00:37:13 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_is_builtin(char *value)
{
	if ((ft_strncmp(value, "echo", 4) == 0) && value[4] == '\0')
		return (1);
	if ((ft_strncmp(value, "cd", 2) == 0) && value[2] == '\0')
		return (1);
	if ((ft_strncmp(value, "pwd", 3) == 0) && value[3] == '\0')
		return (1);
	if ((ft_strncmp(value, "export", 6) == 0) && value[6] == '\0')
		return (1);
	if ((ft_strncmp(value, "unset", 5) == 0) && value[5] == '\0')
		return (1);
	if ((ft_strncmp(value, "env", 3) == 0) && value[3] == '\0')
		return (1);
	if ((ft_strncmp(value, "exit", 4) == 0) && value[4] == '\0')
		return (1);
	return (0);
}

void	ft_handle_buitins_red(t_list *temp)
{
	if (temp->infile != 0)
	{
		if (dup2(temp->infile, 0) == -1)
		{
			perror("dup2");
			ft_exit_status(1);
		}
		close(temp->infile);
	}
	if (temp->outfile != 1)
	{
		if (dup2(temp->outfile, 1) == -1)
		{
			perror("dup2");
			ft_exit_status(1);
		}
		close(temp->outfile);
	}
}

int	ft_execute_one_builtin(t_list *temp, t_data **data)
{
	int	save_std_in;
	int	save_std_out;

	save_std_in = dup(0);
	save_std_out = dup(1);
	if (save_std_in == -1 || save_std_out == -1)
	{
		perror("dup");
		ft_exit_status(1);
	}
	ft_handle_buitins_red(temp);
	ft_execute_builtin(temp, data);
	if (dup2(save_std_in, 0) == -1)
	{
		perror("dup2");
		ft_exit_status(1);
	}
	if (dup2(save_std_out, 1) == -1)
	{
		perror("dup2");
		ft_exit_status(1);
	}
	close(save_std_in);
	close(save_std_out);
	return (ft_exit_status(-1));
}

int	execute_commands(t_data **data)
{
	t_list	*temp;
	int		*tab;
	int		total;

	temp = (*data)->cmd;
	total = 0;
	tab = ft_alloc_tab((*data), &total);
	tcgetattr(STDIN_FILENO, (*data)->term);
	if (temp->first && temp->last && ft_is_builtin(temp->value))
		ft_execute_one_builtin(temp, data);
	else
		ft_pipex(data, tab, total);
	ft_close_descriptors((*data));
	return (ft_exit_status(-1));
}
