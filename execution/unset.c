/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:24 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/05 17:12:34 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_unset(t_list *cmd, t_env **envp)
{
    t_env *prev;
    t_env *head;
    t_env *temp;

    if (!cmd->args || !*envp)
        return (SUCCESS);

    int i = 0;
    while (cmd->args[i])
    {
        prev = NULL;
        temp = NULL;
        head = *envp;

        while (head)
        {
            if (ft_strcmp(cmd->args[i], head->key) == 0)
            {
                if (prev)
                    prev->next = head->next;
                else
                    *envp = head->next;
                temp = head;
                head = head->next;
                free(temp->key);
                temp->key = NULL;
                free(temp->value);
                temp->value = NULL;
                free(temp);
                temp = NULL;
                break;
            }
            prev = head;
            head = head->next;
        }
        i++;
    }
    return (SUCCESS);
}

