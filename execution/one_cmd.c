/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:36:50 by oumimoun          #+#    #+#             */
/*   Updated: 2024/06/03 00:18:12 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

char	*ft_get_path(t_list *cmd, t_env *env, t_data *data)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = -1;
	if (access(cmd->value, X_OK) == 0 \
		&& (cmd->value[0] == '.' || cmd->value[0] == '/'))
		return (gc_strdup(cmd->value, &data->addr));
	paths = ft_get_paths(env, data);
	while (paths && paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd->value);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
	}
	return (NULL);
}

int	count_args(char **args)
{
	int	total;

	total = 0;
	while (args && args[total])
		total++;
	return (total);
}

void	copy_command_args(char **command, t_list *cmd, t_addr *addr)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd->args && cmd->args[j])
	{
		command[i] = gc_strdup(cmd->args[j], &addr);
		i++;
		j++;
	}
	command[i] = NULL;
}

char	**ft_join_for_execve(t_list *cmd, t_addr *addr)
{
	char	**command;
	int		total;

	total = count_args(cmd->args);
	command = ft_calloc(&addr, total + 2, sizeof(char *));
	command[0] = gc_strdup(cmd->value, &addr);
	copy_command_args(command, cmd, addr);
	return (command);
}
