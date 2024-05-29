/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:02:29 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/29 18:06:08 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"

char	*ft_getvalue(char *key, t_env *env, t_addr **addr)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (gc_strdup(env->value, addr));
		env = env->next;
	}
	return (NULL);
}

int	get_key(char *line, int i, int j)
{
	j = 1;
	while ((line[i + j]) && (ft_isalnum(line[i + j]) || line[i + j] == '$'\
	|| line[i + j] == '_' || line[i + j] == '?'))
	{
		j++;
		if (j == 2 && (line[i + j - 1] == '$' || line[i + j - 1] == '?'))
			break ;
		else if (j == 2 && ft_isdigit(line[i + j - 1]))
			break ;
		else if (j > 2 && line[i + j - 1] == '$')
		{
			j--;
			break ;
		}
	}
	return (j);
}

char	*ft_expand(char *key, t_env *env, t_addr **addr)
{
	char	*value;

	if (ft_strncmp(key, "$_", ft_strlen(key)) == 0)
		return (key);
	if (ft_strncmp(key, "$$", ft_strlen(key)) == 0)
		return (key);
	if (ft_strncmp(key, "$?", ft_strlen(key)) == 0)
		return (gc_itoa(ft_exit_status(-1), addr));
	if (key && (ft_strlen(key) == 1 || ft_isdigit(key[1])))
		return (gc_strdup("", addr));
	value = ft_getvalue(key + 1, env, addr);
	if (!value)
		return (gc_strdup("", addr));
	return (value);
}

void	ft_split_value(t_list *curr, char *value, t_addr **addr, t_env *env)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split_sp(value, addr);
	if (!splitted)
		return ;
	if ((!splitted[0] && is_after_red(curr, addr, env)) || !splitted[0] \
		|| (splitted[1] && is_after_red(curr, addr, env)))
	{
		delete_node(curr);
		return ;
	}
	while (splitted[i])
	{
		add_middle(curr, cr_node(splitted[i], WORD, addr));
		curr = curr->nxt;
		if (i == 0)
			delete_node(curr->prv);
		if (splitted[i + 1] && splitted[i + 1][0])
		{
			add_middle(curr, cr_node(gc_strdup(" ", addr), W_SPACE, addr));
			curr = curr->nxt;
		}
		i++;
	}
}

void	expand_all(t_list **list, t_env *env, t_addr **addr)
{
	t_list	*curr;

	curr = *list;
	while (curr)
	{
		if (curr && curr->type == H_DOC)
			find_delimiter(curr);
		else if (curr->type == Q_DOLLAR)
		{
			curr->value = ft_expand(curr->value, env, addr);
			curr->type = WORD;
		}
		else if (curr->type == _DOLLAR)
			ft_split_value(curr, ft_expand(curr->value, env, addr), addr, env);
		if (curr)
			curr = curr->nxt;
	}
}
