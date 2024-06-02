/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:44:18 by oumimoun          #+#    #+#             */
/*   Updated: 2024/06/02 22:23:40 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void	ft_print_error_execute_command(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" command not found\n", 2);
}

void	ft_create_pipe(t_list *temp, t_data *data)
{
	if (!temp->last)
	{
		if (pipe(data->pd) == -1)
			exit(127);
	}
}

void	ft_middle_proccess(t_list *temp, t_data **data)
{
	if ((*data)->pid == 0)
		ft_handle_childs(temp, data);
	handle_parent_pipes(*data, temp);
}

int	ft_pipex(t_data **data, int *tab, int total)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = (*data)->cmd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_exit_status(0);
	while (temp)
	{
		ft_create_pipe(temp, (*data));
		if (temp->type == NULL_TOKEN && temp->infile == 0 \
			&& temp->outfile == 1 && temp->last)
			return (ft_exit_status(-1));
		(*data)->pid = fork();
		if ((*data)->pid == -1)
			return (perror("fork:"), (ERROR));
		tab[i++] = (*data)->pid;
		ft_middle_proccess(temp, data);
		temp = temp->nxt;
	}
	ft_parent_wait((*data), tab, total);
	return (ft_exit_status(-1));
}
