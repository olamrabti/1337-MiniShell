/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:44 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/23 10:17:59 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// TODO testing echo

void ft_echo(char **str)
{
    int no_newline;
    int i;

    no_newline = 0;
    i = 1;
    if (ft_strncmp(str[1], "-n", 2) == 0)
    {
        no_newline = 1;
        i++;
    }
    while (str[i])
    {
        printf("%s", str[i]);
        if (str[i + 1] != NULL)
            printf(" ");
        i++;
    }

    if (!no_newline)
        printf("\n");
}

int main(int argc, char *argv[])
{
    ft_echo(argv);
    return 0;
}