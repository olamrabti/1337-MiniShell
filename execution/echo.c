/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:44 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/21 15:41:51 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// TODO testing echo

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
    unsigned int i;

    i = 0;
    while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
    {
        if (s1[i] != s2[i])
            return ((unsigned char)(s1[i]) - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}

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