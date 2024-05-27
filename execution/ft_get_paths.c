/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:41:27 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/26 22:42:11 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

char	**ft_get_paths(t_env *env, t_data *data)
{
	t_env		*temp;
	char		**path;

	if (!env)
		return (NULL);
	path = NULL;
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PATH", 4) == 0)
		{
			path = ft_split(temp->value, ':', data);
			return (path);
		}
		temp = temp->next;
	}
	return (NULL);
}
