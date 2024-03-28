/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/28 05:38:57 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		execute_builtin(t_shell *shell, t_cmd *command)
{
    if (ft_strcmp(command->av[0], "echo") == 0)
        ft_echo(command);
    else if (ft_strcmp(command->av[0], "cd") == 0)
        ft_cd(shell, command);
    else if (ft_strcmp(command->av[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(command->av[0], "export") == 0)
        ft_export(shell, command);
    else if (ft_strcmp(command->av[0], "unset") == 0)
        ft_unset(shell, command);
    else if (ft_strcmp(command->av[0], "env") == 0)
        ft_env(shell);
    else if (ft_strcmp(command->av[0], "exit") == 0)
        ft_exit(shell, command);
}
