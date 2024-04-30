/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:36:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/30 16:47:35 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// TODO creating cd
// TODO testing cd
//  [ ] cd with no argument
// [ ] cd -
// [ ] cd ~
// [ ] cd chenge oldpwd and pwd

// getcwd();

int ft_cd(t_list *cmd, t_env *env)
{
    (void)env;
    // char static cwd[1024];

    // if (getcwd(cwd, sizeof(cwd)) != NULL)
    // {
    //     printf("Current working directory: %s\n", cwd);
    // }
    // else
    // {
    //     perror("getcwd() error");
    //     return 1;
    // }
    // printf("directpry is == %s\n", cmd->args[0]);
    if (cmd->args)
    {
        if (chdir(cmd->args[0]) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": no such file or directory\n", 2);
            return (-1);
        }
    }

    return (SUCCESS);
}

// getcwd geting PWD

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