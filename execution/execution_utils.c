/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/30 17:58:58 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ]: check if the command is a builtin
// [ ]: execute the builtin
// [ ] pipex

int ft_execute_builtin(t_list *cmd, t_env *env)
{
    if (ft_strncmp(cmd->value, "echo", 4) == 0)
        return (ft_echo(cmd));
    if (ft_strncmp(cmd->value, "cd", 2) == 0)
        return (ft_cd(cmd , env));
    if (ft_strncmp(cmd->value, "pwd", 3) == 0)
        return (ft_pwd(cmd));
    // if (ft_strncmp(cmd->value, "export", 6) == 0)
    //     ft_export();
    // if (ft_strncmp(cmd->value, "unset", 5) == 0)
    //     ft_unset();
    if (ft_strncmp(cmd->value, "env", 3) == 0)
        return (ft_env(cmd, env));
    // if (ft_strncmp(cmd->value, "exit", 4) == 0)
    //     ft_exit();
    return (ERROR);
}





