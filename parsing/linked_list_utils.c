/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:32:43 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/22 10:49:13 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_list	*create_node(char *value, token type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->prv = NULL;
	node->nxt = NULL;
	node->value = value;
	node->type = type;
	node->args = NULL;
	node->infile = 0;
	node->outfile = 1;
	return (node);
}

int	node_addfront(t_list **list, t_list *new)
{
	if (!list || !new)
		return (1);
	new->prv = NULL;
	if (*list)
	{
		(*list)->prv = new;
		new->nxt = *list;
	}
	else
		new->nxt = NULL;
	*list = new;
	return (0);
}

int	node_addback(t_list **list, t_list *new)
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
	free(node);
	node = NULL;
	return (0);
}

void	remove_list(t_list **list)
{
	t_list	*curr;
	t_list	*next;

	if (!list || !*list)
		return ;
	if (!(*list)->nxt)
	{
		delete_node(*list);
		*list = NULL;
		return ;
	}
	curr = *list;
	while (curr != NULL)
	{
		next = curr->nxt;
		delete_node(curr);
		curr = next;
	}
	*list = NULL;
}

void print_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		printf("value: -%s- args : -%s- token : %d\n", temp->value, temp->args, temp->type);
		temp = temp->nxt;
	}
}

t_list *get_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->nxt)
		list = list->nxt;
	return (list);
}