/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:07:01 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/18 09:07:27 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

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

