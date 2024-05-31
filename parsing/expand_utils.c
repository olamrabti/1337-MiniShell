/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:13:44 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/31 14:46:27 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

static char	*put_str(int n, char *str, int count)
{
	str[count] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		while (--count)
		{
			str[count] = n % 10 + 48;
			n /= 10;
		}
		return (str);
	}
	while (count--)
	{
		str[count] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

char	*gc_itoa(int n, t_addr **addr)
{
	size_t	count;
	int		temp;
	char	*str;

	count = 1;
	temp = n;
	while (temp / 10)
	{
		temp /= 10;
		count++;
	}
	if (n < 0)
		count++;
	str = (char *)ft_calloc(addr, sizeof(char), count + 1);
	if (!str)
		return (NULL);
	return (put_str(n, str, count));
}

void	empty_cmd(t_list *temp, t_addr **addr, t_env *env)
{
	int	fd;

	fd = -1;
	while (temp && temp->type != PIPE && temp->type != NULL_TOKEN)
	{
		if (temp->nxt && temp->type == H_DOC)
			close(fill_heredoc(temp->nxt, addr, env));
		temp->type = RM;
		temp = temp->prv;
	}
	if (temp && (temp->type == PIPE || temp->type == NULL_TOKEN))
	{
		add_middle(temp, cr_node(NULL, NULL_TOKEN, addr));
		temp = temp->nxt->nxt;
	}
	while (temp)
	{
		if (temp->type == PIPE)
			break ;
		if (temp->nxt && temp->type == H_DOC)
			close(fill_heredoc(temp->nxt, addr, env));
		temp->type = RM;
		temp = temp->nxt;
	}
}

int	is_after_red(t_list *curr, t_addr **addr, t_env *env)
{
	t_list	*tmp;

	tmp = curr;
	if (tmp->prv)
		tmp = tmp->prv;
	while (tmp && tmp->type == W_SPACE)
		tmp = tmp->prv;
	if (!tmp)
		return (0);
	if (tmp->type == RED_IN || tmp->type == RED_OUT || tmp->type == R_O_APPEND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(curr->value, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		ft_exit_status(1);
		empty_cmd(tmp, addr, env);
		return (1);
	}
	return (0);
}

void	find_delimiter(t_list *list)
{
	t_list	*temp;

	temp = list;
	if (temp->nxt)
		temp = temp->nxt;
	while (temp && temp->type == W_SPACE)
	{
		delete_node(temp);
		temp = temp->nxt;
	}
	if (temp && temp->type == Q_DOLLAR)
		temp->type = LTRAL;
	if (temp && temp->type == _DOLLAR)
		temp->type = WORD;
}
