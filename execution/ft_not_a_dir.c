/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_a_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:38:52 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/29 17:40:50 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void	ft_not_a_dir(t_list *temp, t_data *data)
{
	char	*new_cmd;

	if (temp->value[ft_strlen(temp->value) - 1] == '/')
	{
		new_cmd = gc_substr(temp->value, 0, \
			ft_strlen(temp->value) - 1, &data->addr);
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
