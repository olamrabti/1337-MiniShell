/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:42:07 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/25 15:12:07 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

t_list	*cr_node(char *value, token type, t_addr **addr)
{
	t_list	*node;

	node = ft_calloc(addr, 1, sizeof(t_list));
	if (!node)
		return (NULL);
	node->prv = NULL;
	node->nxt = NULL;
	node->value = value;
	node->type = type;
	node->args = NULL;
	node->infile = 0;
	node->outfile = 1;
	node->first = 0;
	node->last = 0;
	return (node);
}

int	add_middle(t_list *curr, t_list *new)
{
	if (!curr || !new)
		return (1);
	new->nxt = curr->nxt;
	new->prv = curr;
	if (curr->nxt)
		curr->nxt->prv = new;
	curr->nxt = new;
	return (0);
}

int	addback(t_list **list, t_list *new)
{
	t_list	*temp;

	if (!list || !new)
		return (1);
	new->nxt = NULL;
	if (!*list)
	{
		*list = new;
		return (0);
	}
	temp = *list;
	while (temp->nxt != NULL)
		temp = temp->nxt;
	temp->nxt = new;
	new->prv = temp;
	return (0);
}

int	delete_node(t_list *node)
{
	if (!node)
		return (1);
	if (node->prv)
		node->prv->nxt = node->nxt;
	if (node->nxt)
		node->nxt->prv = node->prv;
	node = NULL;
	return (0);
}

t_list	*get_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->nxt)
		list = list->nxt;
	return (list);
}

// NOTE delete me before push 

void print_list(t_list *list)
{
	t_list *temp;
	char **arg;

	printf("\n===================\n");
	temp = list;
	while (temp)
	{
		printf("value: -%s- args : ", temp->value);
		if (temp->args)
		{
			arg = temp->args;
			while (arg && *arg)
				printf(" -%s- , ", *(arg++));
		}
		printf("first : %d last: %d infile: %d outfile: %d type: %d\n", temp->first, temp->last, temp->infile, temp->outfile, temp->type);
		temp = temp->nxt;
	}
}
