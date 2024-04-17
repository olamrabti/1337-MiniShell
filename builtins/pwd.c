/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:32:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/17 16:11:19 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(char **str)
{
    char *buf;

    buf = getcwd(NULL, 0);
    if (buf == NULL)
    {
        perror("pwd");
        return ;
    }
    printf("%s\n", buf);
    free(buf);
}
int main(int ac, char **av)
{
    ft_pwd(av);
    return (0);
}