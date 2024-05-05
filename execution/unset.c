/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:24 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/05 14:06:03 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

// void ft_lstdelone(t_list *lst, void (*del)(void *))
// {
//     if (lst && del)
//     {
//         del(lst->content);
//         free(lst);
//     }
// }

int ft_unset(t_list *cmd, t_env **envp)
{
    t_env **env;
    // t_env *temp;

    if (cmd->args)
    {
        int i = 0;
        while (cmd->args[i])
        {
            env = envp;
            while (*env)
            {
                if (strcmp(cmd->args[i], (*env)->key) == 0)
                {
                    // Unset the variable by removing it from the linked list
                    t_env *temp = *env;
                    *env = (*env)->next;
                    free(temp->key);
                    free(temp->value);
                    free(temp);
                    break; // Exit the inner loop once the variable is unset
                }
                env = &(*env)->next;
            }
            i++;
        }
    }

    return SUCCESS;
}