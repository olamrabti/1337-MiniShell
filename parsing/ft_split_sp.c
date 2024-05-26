/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:33:25 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/25 14:34:21 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int		i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	while (--size && *src)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = '\0';
	while (*(src++))
		i++;
	return (i);
}

static size_t	count_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			count++;
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**str_split(char const *s, size_t i, size_t len, t_addr **addr)
{
	char	**copy;
	size_t	j;
	size_t	count;

	j = 0;
	count = count_words(s);
	copy = (char **)ft_calloc(addr, (count + 1), sizeof(char *));
	if (!copy)
		return (NULL);
	while (j < count)
	{
		len = 0;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		while (s[i + len] && s[i + len] != ' ' && s[i + len] != '\t')
			len++;
		copy[j] = (char *)ft_calloc(addr, (len + 1), sizeof(char));
		if (!copy[j])
			return (NULL);
		ft_strlcpy(copy[j], (s + i), len + 1);
		i += len;
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

char	**ft_split_sp(char const *s, t_addr **addr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	return (str_split(s, i, len, addr));
}
