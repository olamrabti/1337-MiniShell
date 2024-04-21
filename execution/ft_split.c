/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:08:23 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/21 15:41:51 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	count_str(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (str[i] == c))
			i++;
		if (str[i])
			count++;
		while (str[i] != '\0' && (str[i] != c))
			i++;
	}
	return (count);
}

static int	len_str(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_allocated_str(const char *str, char c)
{
	char	*result;
	int		len_string;

	len_string = len_str(str, c);
	result = (char *)malloc((len_string + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len_string] = '\0';
	while (len_string--)
		result[len_string] = str[len_string];
	return (result);
}

static void	ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_str(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			result[i] = ft_allocated_str(s, c);
			if (!result[i])
				return (ft_free(result), NULL);
			i++;
		}
		while (*s && (*s != c))
			s++;
	}
	result[i] = NULL;
	return (result);
}
