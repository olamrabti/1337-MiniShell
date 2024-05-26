/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:03:07 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/25 15:39:24 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

int	is_operator(t_list *curr, char *line, int *i, t_addr **addr)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		addback(&curr, cr_node(gc_strdup("<<", addr), H_DOC, addr));
		*i += 1;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		addback(&curr, cr_node(gc_strdup(">>", addr), R_O_APPEND, addr));
		*i += 1;
	}
	else if (line[*i] == '>')
		addback(&curr, cr_node(gc_strdup(">", addr), RED_OUT, addr));
	else if (line[*i] == '<')
		addback(&curr, cr_node(gc_strdup("<", addr), RED_IN, addr));
	else if (line[*i] == '|')
		addback(&curr, cr_node(gc_strdup("|", addr), PIPE, addr));
	else if (line[*i] == '"')
		addback(&curr, cr_node(gc_strdup("\"", addr), D_QUOTE, addr));
	else if (line[*i] == '\'')
		addback(&curr, cr_node(gc_strdup("'", addr), S_QUOTE, addr));
	else
		return (0);
	return (1);
}

void	is_word(t_list *curr, char *line, int *i, t_addr **addr)
{
	curr = get_last_node(curr);
	if (curr && curr->type == WORD)
		curr->value = ft_charjoin(curr->value, line[*i], addr);
	else
		addback(&curr, cr_node(ft_charjoin(NULL, line[*i], addr), WORD, addr));
}

int	count_spaces(char *line)
{
	int	j;

	j = 1;
	while (line[j] && ft_isspace(line[j]))
		j += 1;
	return (j);
}

void	ms_tokenize(t_list *curr, char *str, t_addr **a, int *j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			*j = get_key(str, i, *j);
			if (*j == 1 && str[i + 1]
				&& (str[i + 1] == '\'' || str[i + 1] == '"'))
				addback(&curr, cr_node(ft_strndup(&str[i], *j, a), RM, a));
			else
				addback(&curr, cr_node(ft_strndup(&str[i], *j, a), _DOLLAR, a));
			i += *j - 1;
		}
		else if (ft_isspace(str[i]))
		{
			*j = count_spaces(&str[i]);
			addback(&curr, cr_node(ft_strndup(&str[i], *j, a), W_SPACE, a));
			i += *j - 1;
		}
		else if (!is_operator(curr, str, &i, a))
			is_word(curr, str, &i, a);
		i++;
	}
}

t_list	*init_list(char *line, t_addr **addr)
{
	t_list	*head;
	t_list	*curr;
	int		j;

	j = 1;
	head = cr_node(NULL, NULL_TOKEN, addr);
	curr = head;
	ms_tokenize(curr, line, addr, &j);
	return (head);
}
