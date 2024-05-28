/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:02 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/28 18:49:01 by oumimoun         ###   ########.fr       */
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

int	execute_commands(t_data **data, char **envp)
{
	t_list	*temp;
	int		*tab;
	int		total;

	temp = (*data)->cmd;
	total = 0;
	tab = ft_alloc_tab((*data), &total);
	if (!data)
		return (ERROR);
	tcgetattr(STDIN_FILENO, (*data)->term);
	if (temp->first && temp->last && ft_is_builtin(temp->value))
		return (ft_execute_builtin(temp, *data));
	ft_pipex((*data), envp, tab, total);
	return (SUCCESS);
}
