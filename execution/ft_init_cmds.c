/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:21:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/26 11:25:16 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

void ft_init_cmds(t_data *data)
{
    t_list *temp;
    t_list *current;

    temp = data->cmd;
    temp = temp->nxt;
    if (temp != NULL)
    {
        if (temp->nxt == NULL)
        {
            temp->first = 1;
            temp->last = 1;
        }
        else
        {
            temp->first = 1;
            temp->last = 0;
            t_list *current = temp->nxt;
            while (current->nxt)
            {
                current->first = 0;
                if (current->nxt == NULL)
                    current->last = 1;
                else
                    current->last = 0;
                current = current->nxt;
            }
        }
    }
}

