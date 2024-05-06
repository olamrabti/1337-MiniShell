/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:32:43 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/06 12:24:56 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"


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
	node->first = 0;
	node->last = 0;
	return (node);
}

int node_add_middle(t_list *curr, t_list *new)
{
    if (!curr || !new)
        return 1;
    new->nxt = curr->nxt;
    new->prv = curr;
    if (curr->nxt)
        curr->nxt->prv = new;
    curr->nxt = new;
    return 0;
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
	// free(node);
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
		printf("first : %d last: %d infile: %d outfile: %d type: %d\n",temp->first, temp->last, temp->infile, temp->outfile, temp->type);
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