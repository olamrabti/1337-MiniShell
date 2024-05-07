/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/06 12:36:14 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [ ]: check if the command is a builtin
// [ ]: execute the builtin
// [ ] pipex

int ft_execute_builtin(t_list *cmd, t_data *data)
{
    if (ft_strncmp(cmd->value, "echo", 4) == 0)
        return (ft_echo(cmd));
    if (ft_strncmp(cmd->value, "cd", 2) == 0)
        return (ft_cd(cmd, data->env));
    if (ft_strncmp(cmd->value, "pwd", 3) == 0)
        return (ft_pwd(cmd));
    if (ft_strncmp(cmd->value, "export", 6) == 0)
        return (ft_export(cmd, &data->env));
    if (ft_strncmp(cmd->value, "unset", 5) == 0)
        return (ft_unset(cmd , &data->env));
    if (ft_strncmp(cmd->value, "env", 3) == 0)
        return (ft_env(cmd, &data->env));
    if (ft_strncmp(cmd->value, "exit", 4) == 0)
        return (ft_exit(cmd));
    return (ERROR);
}

