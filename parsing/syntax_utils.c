/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:31:48 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/31 14:55:13 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

int	ft_isdigit(int d)
{
	if (d >= '0' && d <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int d)
{
	if (d == ' ' || (d >= 9 && d <= 13))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

void print_syntax_err(char *value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("'\n", 2);
}

int	check_syntax(t_list **list, int *count)
{
	t_list	*crr;

	crr = *list;
	while (crr)
	{
		if (crr->type == PIPE)
		{
			if ((crr->prv && !crr->prv->prv)
				|| !crr->nxt || (crr->nxt && crr->nxt->type == PIPE))
				return (print_syntax_err("|"), 1);
		}
		if (crr->type == RED_IN || crr->type == RED_OUT
			|| crr->type == R_O_APPEND || crr->type == H_DOC)
		{
			if ((!crr->nxt))
				return (print_syntax_err("newline"), 1);
			if (crr->nxt && crr->nxt->type != WORD && crr->nxt->type != LTRAL)
				return (print_syntax_err(crr->nxt->value), 1);
			(*count)++;
		}
		crr = crr->nxt;
	}
	return (0);
}
