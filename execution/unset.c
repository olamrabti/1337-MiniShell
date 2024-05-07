/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:01:24 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/06 15:13:26 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_valid_unset(char *str)
{
    int i = 0;
    if (ft_isalpha(str[0]) || str[0] == '_')
    {
        i++;
        while (str[i] && (str[i] != '=' && str[i] != '+'))
        {
            if (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            else
                return 0;
        }
    }
    else
        return (0);
    return (1);
}



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
        if (ft_valid_unset(cmd->args[i]))
        {
            prev = NULL;
            temp = NULL;
            head = *envp;

            while (head)
            {
                if (ft_strcmp(cmd->args[i], head->key) == 0)
                {
                    printf("[%p] mn hadi \n", *envp);
                    printf("[%p]\n", head->next);
                    if (prev)
                        prev->next = head->next;
                    else
                        *envp = head->next;
                    printf("[%p] it should be different\n", *envp);
                    temp = head;
                    head = head->next;

                    free(temp->key);
                    temp->key = NULL;
                    free(temp->value);
                    temp->value = NULL;
                    printf("[%p]\n", temp);
                    free(temp);
                    temp = NULL;

                    return (SUCCESS);
                }
                prev = head;
                head = head->next;
            }
        }
        else
        {
            ft_putstr_fd("nset: ", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd(": not a valid identifier", 2);
        }
        i++;
    }
    return (SUCCESS);
}
