/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:32:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/25 10:05:54 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ] OLDPWD
// [ ] "~"

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
