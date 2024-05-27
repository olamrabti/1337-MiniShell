/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:32:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/26 22:53:39 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

char	*ft_get_cwd(char *new_path, int flag)
{
	static char	static_path[PATH_MAX];
	char		path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_strlcpy(static_path, path, PATH_MAX);
		return (static_path);
	}
	if (flag == 1)
	{
		ft_strlcat(static_path, "/", PATH_MAX);
		ft_strlcat(static_path, new_path, PATH_MAX);
	}
	return (static_path);
}

int	ft_pwd(t_list *cmd)
{
	char	*path;

	(void)cmd;
	path = ft_get_cwd(NULL, 0);
	printf("%s\n", path);
	return (SUCCESS);
}
