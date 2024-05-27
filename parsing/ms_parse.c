/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:49:30 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/27 15:55:10 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

void	remove_token(t_list **list, t_token token)
{
	t_list	*temp;

	temp = *list;
	while (temp)
	{
		if (temp->type == token)
			delete_node(temp);
		if (temp)
			temp = temp->nxt;
	}
}

int	fill_data(t_data **data, t_list *list)
{
	t_list	*last;

	remove_token(&list, RM);
	if (list->nxt)
	{
		list = list->nxt;
		list->first = 1;
		delete_node(list->prv);
	}
	handle_args(&list, &((*data)->addr));
	remove_token(&list, PIPE);
	last = get_last_node(list);
	if (last)
		last->last = 1;
	(*data)->cmd = list;
	return (0);
}

int	ms_parse(t_data **data, char *line, t_env *env)
{
	t_list	*list;
	int		count;

	count = 0;
	list = init_list(line, &((*data)->addr));
	if (!list)
		return (1);
	if (handle_quote(&list, S_QUOTE, &((*data)->addr)) % 2 != 0)
		return (printf("quote>\n"), 1);
	remove_token(&list, RM);
	expand_all(&list, env, &((*data)->addr));
	remove_token(&list, RM);
	concat_words(&list, &((*data)->addr));
	remove_token(&list, W_SPACE);
	(*data)->fds = malloc((count + 1) * sizeof(int));
	if ((*data)->fds == NULL)
		return (1);
	if (check_syntax(&list, &count) == 1)
		return (ft_close_descriptors(*data), ft_exit_status(258), 1);
	(*data)->fds = handle_redirections(&list, &count, data, env);
	if (g_signal == 2)
		return (ft_close_descriptors(*data), 1);
	return (fill_data(data, list));
}
