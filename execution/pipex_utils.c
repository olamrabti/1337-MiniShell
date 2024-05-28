/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:45:19 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/28 23:36:14 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_parent_wait(t_data *data, int *tab, int total)
{
	int	status;
	int	i;

	close(data->save);
	i = 0;
	while (i < total)
	{
		waitpid(tab[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, data->term);
		write(1, "Quit: 3\n", 8);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, data->term);
		write(1, "\n", 1);
	}
	if (WIFEXITED(status))
		ft_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_exit_status(WTERMSIG(status) + 128);
	return (SUCCESS);
}

int	ft_close_descriptors(t_data *data)
{
	int	i;

	i = 0;
	if (data && data->fds)
	{
		while (data->fds[i])
		{
			if (data->fds[i] == -2)
				return (SUCCESS);
			close(data->fds[i]);
			i++;
		}
	}
	return (SUCCESS);
}

void	handle_file_descriptors(t_list *temp)
{
	if (temp->infile != 0)
	{
		if (temp->infile == -1)
			exit(1);
		if (dup2(temp->infile, 0) == -1)
			perror("infile");
		close(temp->infile);
	}
	if (temp->outfile != 1)
	{
		if (temp->outfile == -1)
			exit(1);
		if (dup2(temp->outfile, 1) == -1)
			perror("outfile");
		close(temp->outfile);
	}
}

int	ft_execute(t_list *cmd, t_data *data, char **envp)
{
	char	*path;
	char	**command;
	int		i;

	i = 0;
	path = ft_get_path(cmd, data->env, data);
	if (!path)
		return (-1);
	command = ft_join_for_execve(cmd, data->addr);
	if (!command)
		return (-1);
	envp = convert_envp(data->env, &data->addr_env);
	return (execve(path, command, envp));
}

int	*ft_alloc_tab(t_data *data, int *total)
{
	t_list	*tmp;
	int		*tab;

	tmp = data->cmd;
	while (tmp)
	{
		(*total)++;
		tmp = tmp->nxt;
	}
	tab = ft_calloc(&data->addr, (*total), sizeof(int));
	return (tab);
}
