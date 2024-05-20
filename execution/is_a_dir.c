/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:31:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/20 16:20:36 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_is_point(char *str)
{
    if (str[0] == '.' && str[1] == '\0')
        return (1);
    return (0);
}

int ft_is_a_dir(char *str)
{
    int i;

    if (ft_is_point(str))
        return (1);
    i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

// int ft_only_points(char *str)
// {
//     int i = 0;
    
//     while (str[i])
//     {
//         if (str[i] == '.')
//         {
//             i++;
//         }
//         else
//             return 0;
        
//     }
//     return 1;
// }

// int ft_is_point_slash(char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '/' || str[i] == '.')
//             i++;
//         else
//             return (0);
//     }
//     return (1);
// }

int ft_handle_dir(char *str)
{
    int i = 0;

    if (ft_is_point(str))
    {
        ft_putstr_fd("minishell: .: filename argument required\n", 2);
        ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
        return (ft_exit_status(2));
    }
    else
    {
        // [ ] hna 3yet l function stat wla opendir()
        
    }
    
}

