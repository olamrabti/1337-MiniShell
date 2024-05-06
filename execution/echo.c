/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:44 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/05 14:07:13 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// TODO testing echo
// [x] -nnn---nnnn
// [x] strncmp echooooooolkkh
// [x] echo -nnnnnnnnnnnnnnnnnnnnn -nnnn "." "."

static int ft_is_n(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == 'n')
            i++;
        else
            return (0);
    }
    return (1);
}

int ft_echo(t_list *cmd)
{
    int no_newline;
    int i;

    no_newline = 0;
    i = 0;
    if (cmd->args)
    {
        while ((ft_strncmp(cmd->args[i], "-n", 2) == 0) && ft_is_n(cmd->args[i] + 1))
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
    return (SUCCESS);
}
