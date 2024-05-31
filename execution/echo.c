/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:44 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/31 15:40:18 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

static int	ft_is_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_echo_fd(t_list *cmd)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 0;
	while ((ft_strncmp(cmd->args[i], "-n", 2) == 0)
		&& ft_is_n(cmd->args[i] + 1))
	{
		no_newline = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->outfile);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", cmd->outfile);
		i++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", cmd->outfile);
}

void	ft_echo_printf(t_list *cmd)
{
	int	no_newline;
	int	i;

	i = 0;
	no_newline = 0;
	if (cmd->args)
	{
		while ((ft_strncmp(cmd->args[i], "-n", 2) == 0)
			&& ft_is_n(cmd->args[i] + 1))
		{
			no_newline = 1;
			i++;
		}
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (!no_newline)
		printf("\n");
}

int	ft_echo(t_list *cmd)
{
	ft_exit_status(0);
	if (cmd->args && cmd->last && cmd->first)
	{
		ft_echo_fd(cmd);
		return (SUCCESS);
	}
	ft_echo_printf(cmd);
	return (SUCCESS);
}
