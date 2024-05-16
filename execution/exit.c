/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:02:32 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/10 12:16:31 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

static int	check_overflow(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	size_t				i;
	int					signe;
	unsigned long long	total;

	i = 0;
	signe = 1;
	total = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (total > (9223372036854775807ULL - (str[i] - '0')) / 10)
			return (check_overflow(signe));
		total = total * 10 + str[i] - '0';
		i++;
	}
	return ((int)(signe * total));
}

int ft_valid_exit(char *str)
{
    int i = 0;
    if (str[0] == '+' || str[0] == '-' || ft_isdigit(str[0]))
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int ft_exit(t_list *cmd)
{
    if (cmd->args)
    {
        if (ft_valid_exit(cmd->args[0]) && !cmd->args[1])
        {
            int ext = ft_atoi(cmd->args[0]);
            exit(ext % 256);
        }
        else if (ft_valid_exit(cmd->args[0]) && cmd->args[1])
        {
            ft_putstr_fd("exit: too many arguments\n", 2);
            return (ERROR);
        }
        else
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            exit(255);
        }
    }
    else
        exit(0);
    return (SUCCESS);
}
