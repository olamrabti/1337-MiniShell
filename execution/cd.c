/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/25 10:05:04 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// TODO creating cd
// TODO testing cd
//  [ ] cd with no argument



void ft_cd(char *str)
{
    if (chdir(str) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd(": no such file or directory\n", 2);
    }
}

// int main(int argc, char *argv[])
// {
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
//         return 1;
//     }

//     ft_cd(argv[1]);

//     return 0;
// }