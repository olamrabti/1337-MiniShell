/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:44 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/30 18:03:35 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// TODO testing echo

int ft_echo(t_list *cmd)
{
    int no_newline;
    int i;

    no_newline = 0;
    i = 0;
    if (ft_strncmp(cmd->args[0], "-n", 2) == 0)
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

    if (!no_newline)
        printf("\n");
    return (SUCCESS);
}
