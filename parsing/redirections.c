/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:44:38 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/29 16:10:13 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

void	assign_fd(t_list *tmp, t_addr **addr)
{
	int	in;
	int	out;

	in = tmp->infile;
	out = tmp->outfile;
	tmp = tmp->nxt;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			add_middle(tmp->prv, cr_node(NULL, NULL_TOKEN, addr));
			break ;
		}
		if (tmp->type != RM)
		{
			tmp->infile = in;
			tmp->outfile = out;
			break ;
		}
		if (!tmp->nxt)
			addback(&tmp, cr_node(NULL, NULL_TOKEN, addr));
		tmp = tmp->nxt;
	}
}

int	get_fd(t_list *crr, t_list *tmp, t_addr **ad, t_env *env)
{
	if (crr->type == RED_IN)
	{
		tmp->infile = open(crr->nxt->value, O_RDWR);
		if (tmp->infile == -1)
		{
			perror(crr->nxt->value);
			empty_cmd(crr, ad, env);
		}
		return (tmp->infile);
	}
	if (crr->type == R_O_APPEND)
		tmp->outfile = open(crr->nxt->value, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		tmp->outfile = open(crr->nxt->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp->outfile == -1)
	{
		perror(crr->nxt->value);
		empty_cmd(crr, ad, env);
	}
	return (tmp->outfile);
}

int	open_file(t_list *curr, t_list *tmp, t_addr **addr, t_env *env)
{
	if (tmp->infile >= 0 && tmp->outfile >= 0
		&& (curr->type == RED_OUT || curr->type == R_O_APPEND))
	{
		tmp->outfile = get_fd(curr, tmp, addr, env);
		return (curr->type = RM, curr->nxt->type = RM, tmp->outfile);
	}
	if (tmp->infile >= 0 && tmp->outfile >= 0 && curr->type == RED_IN)
	{
		tmp->infile = get_fd(curr, tmp, addr, env);
		return (curr->type = RM, curr->nxt->type = RM, tmp->infile);
	}
	curr->type = RM;
	curr->nxt->type = RM;
	return (-1);
}

int	open_heredoc(t_list *curr, t_list *tmp, t_addr **addr, t_env *env)
{
	curr->type = RM;
	tmp->infile = fill_heredoc(curr->nxt, addr, env);
	curr->nxt->type = RM;
	return (tmp->infile);
}

int	*handle_redirections(t_list **list, int *count, t_data **data, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;
	int		i;

	(*data)->fds[*count] = -2;
	curr = *list;
	tmp = *list;
	i = 0;
	while (curr)
	{
		if (curr->type == RED_OUT
			|| curr->type == R_O_APPEND || curr->type == RED_IN)
			(*data)->fds[i++] = open_file(curr, tmp, &(*data)->addr, env);
		else if (curr->type == H_DOC)
			(*data)->fds[i++] = open_heredoc(curr, tmp, &(*data)->addr, env);
		curr = curr->nxt;
		if (!curr || curr->type == PIPE)
		{
			assign_fd(tmp, &(*data)->addr);
			if (curr && curr->type == PIPE)
				tmp = curr;
		}
	}
	return ((*data)->fds);
}
