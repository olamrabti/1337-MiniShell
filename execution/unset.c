/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:24 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/29 00:04:39 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	ft_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		i++;
		while (str[i] && (str[i] != '=' && str[i] != '+'))
		{
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_print_error_unset(char *str)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	ft_exit_status(1);
}

void	unset_env_variable(char *arg, t_env **envp)
{
	t_env	*prev;
	t_env	*temp;
	t_env	*head;

	prev = NULL;
	temp = NULL;
	head = *envp;
	while (head)
	{
		if (ft_strcmp(arg, head->key) == 0)
		{
			if (prev)
				prev->next = head->next;
			else
				*envp = head->next;
			temp = head;
			head = head->next;
			free_env_node(temp);
		}
		else
		{
			prev = head;
			head = head->next;
		}
	}
}

void	process_unset_command(t_list *cmd, t_env **envp)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (ft_valid_unset(cmd->args[i]))
			unset_env_variable(cmd->args[i], envp);
		else
			ft_print_error_unset(cmd->args[i]);
		i++;
	}
}

int	ft_unset(t_list *cmd, t_env **envp)
{
	if (!cmd->args || !*envp)
		return (SUCCESS);
	process_unset_command(cmd, envp);
	return (ft_exit_status(-1));
}
