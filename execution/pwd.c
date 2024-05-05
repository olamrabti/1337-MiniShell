/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:32:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/30 16:42:13 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ] OLDPWD
// [ ] "~"

int ft_pwd(t_list *cmd)
{
    (void)cmd;
    char *buf;

    buf = getcwd(NULL, 0);
    if (buf == NULL)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", buf);
    free(buf);
    return (SUCCESS);
}
