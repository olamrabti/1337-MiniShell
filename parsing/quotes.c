/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:40:06 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/25 15:43:27 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

void	is_emptystr(t_list *curr, t_addr **addr)
{
	char	*tmp;

	tmp = gc_strdup("", addr);
	curr->type = LTRAL;
	curr->value = tmp;
}

void	join_ltrals(t_list *curr, t_list *next, t_addr **addr)
{
	char	*tmp;

	tmp = gc_strjoin(curr->value, next->value, addr);
	delete_node(next);
	curr->value = tmp;
	curr->type = LTRAL;
}

t_list	*handle_doubleq(t_list *curr, int *i, t_addr **addr)
{
	char	*tmp;

	tmp = NULL;
	curr->type = RM;
	curr = curr->nxt;
	if (curr && curr->type == D_QUOTE)
		return ((*i)++, is_emptystr(curr, addr), curr);
	else if (curr && curr->type != _DOLLAR)
		curr->type = LTRAL;
	while (curr && curr->nxt && curr->type != D_QUOTE)
	{
		if (curr->type != _DOLLAR && curr->type != Q_DOLLAR
			&& curr->nxt && curr->nxt->type != D_QUOTE
			&& curr->nxt->type != _DOLLAR)
			join_ltrals(curr, curr->nxt, addr);
		if (curr->type == _DOLLAR)
			curr->type = Q_DOLLAR;
		if (curr->type != _DOLLAR && curr->type != Q_DOLLAR)
			curr->type = LTRAL;
		curr = curr->nxt;
	}
	return (curr);
}

t_list	*handle_singleq(t_list *curr, int *i, t_addr **addr)
{
	char	*tmp;

	tmp = NULL;
	curr->type = RM;
	curr = curr->nxt;
	if (curr && curr->type == S_QUOTE)
		return ((*i)++, is_emptystr(curr, addr), curr);
	else if (curr)
		curr->type = LTRAL;
	while (curr && curr->nxt && curr->type != S_QUOTE)
	{
		if (curr->nxt && curr->nxt->type != S_QUOTE)
			join_ltrals(curr, curr->nxt, addr);
		curr->type = LTRAL;
		curr = curr->nxt;
	}
	return (curr);
}

int	handle_quote(t_list **list, token quote, t_addr **addr)
{
	t_list	*curr;
	int		i;

	curr = *list;
	i = 2;
	while (curr)
	{
		if ((curr->type == S_QUOTE || curr->type == D_QUOTE) && i % 2 == 0)
		{
			i++;
			quote = curr->type;
			if (curr->type == S_QUOTE)
				curr = handle_singleq(curr, &i, addr);
			else if (curr->type == D_QUOTE)
				curr = handle_doubleq(curr, &i, addr);
		}
		if (curr && curr->type == quote)
		{
			curr->type = RM;
			i++;
		}
		if (curr)
			curr = curr->nxt;
	}
	return (i);
}
