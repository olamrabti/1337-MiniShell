/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:51:51 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/25 14:58:16 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

int	fill_args(t_list *curr, int count, t_addr **addr)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(addr, count, sizeof(char *));
	if (!tmp)
		return (1);
	tmp[--count] = NULL;
	i = 0;
	while (count && curr && curr->prv)
	{
		tmp[--count] = curr->value;
		curr->type = RM;
		if (curr->outfile != 1)
			curr->prv->outfile = curr->outfile;
		curr = curr->prv;
	}
	if (curr)
		curr->args = tmp;
	return (0);
}

void	handle_args(t_list **list, t_addr **addr)
{
	t_list	*curr;
	int		count;

	curr = *list;
	while (curr)
	{
		if (curr && curr->type != PIPE && curr->type != NULL_TOKEN)
		{
			count = 1;
			while (curr && curr->nxt && curr->nxt->type != PIPE)
			{
				count++;
				curr = curr->nxt;
			}
			if (curr && count > 1)
				fill_args(curr, count, addr);
		}
		if (curr)
			curr = curr->nxt;
	}
	remove_token(list, RM);
}

void	concat_words(t_list **list, t_addr **addr)
{
	t_list	*curr;
	char	*tmp;

	curr = *list;
	while (curr)
	{
		if ((curr->type == WORD || curr->type == NF_VAR || curr->type == LTRAL)
			&& curr->nxt
			&& (curr->nxt->type == WORD || curr->nxt->type == NF_VAR
				|| curr->nxt->type == LTRAL))
		{
			tmp = gc_strjoin(curr->value, curr->nxt->value, addr);
			curr->value = tmp;
			if (curr->type == LTRAL || curr->nxt->type == LTRAL)
				curr->type = LTRAL;
			else
				curr->type = WORD;
			delete_node(curr->nxt);
		}
		else
			curr = curr->nxt;
	}
}
