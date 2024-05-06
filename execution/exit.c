/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:02:32 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/06 15:46:19 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_exit(t_list *cmd)
{
    if (cmd->args)
    {
        if (cmd->args[1])
        {
            ft_putstr_fd("", 2);
            exit(255);
        }
        if (ft_valid_exit(cmd->args[0]))
        {
            int ext = ft_atoi(cmd->args[0]);
            exit(ext % 255);
        }
        else
        {
            ft_putstr_fd("", 2);
            exit(255);
        }
        
    }
    else
        exit(0);
    return (SUCCESS);
}
