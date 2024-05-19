/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/18 17:41:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// [x]: check if the command is a builtin
// [x]: execute the builtin
// [x] pipex

int ft_execute_builtin(t_list *cmd, t_data *data)
{
    int status;

    if (ft_strncmp(cmd->value, "echo", 4) == 0)
        status = ft_echo(cmd);
    if (ft_strncmp(cmd->value, "cd", 2) == 0)
        status = ft_cd(cmd, &data->env, data);
    if (ft_strncmp(cmd->value, "pwd", 3) == 0)
        status = ft_pwd(cmd);
    if (ft_strncmp(cmd->value, "export", 6) == 0)
        status = ft_export(cmd, &data->env, data);
    if (ft_strncmp(cmd->value, "unset", 5) == 0)
        status = ft_unset(cmd , &data->env);
    if (ft_strncmp(cmd->value, "env", 3) == 0)
        status = ft_env(cmd, &data->env, data);
    if (ft_strncmp(cmd->value, "exit", 4) == 0)
        status = ft_exit(cmd);
    if (status)
        ft_exit_status(status);
    return (SUCCESS);
}

