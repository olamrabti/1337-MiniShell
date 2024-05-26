/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:37:18 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/25 14:39:17 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = 0;
	if (dest > source)
	{
		while (len > 0)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dst);
}

char	*gc_strjoin(char *s1, char *s2, t_addr **addr)
{
	char	*arr;
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	dest = s1;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(dest);
	s2_len = ft_strlen(s2);
	arr = (char *)ft_calloc(addr, (s1_len + s2_len + 1), sizeof(char));
	if (!arr)
		return (NULL);
	ft_memmove(arr, dest, s1_len);
	ft_memmove(arr + s1_len, s2, s2_len);
	arr[s1_len + s2_len] = '\0';
	return (arr);
}

char	*ft_charjoin(char *s1, char c, t_addr **addr)
{
	char	*arr;
	char	*dest;
	size_t	s1_len;

	dest = s1;
	if (!s1)
	{
		arr = (char *)ft_calloc(addr, 2, sizeof(char));
		if (!arr)
			return (NULL);
		arr[0] = c;
		arr[1] = '\0';
		return (arr);
	}
	s1_len = ft_strlen(dest);
	arr = (char *)ft_calloc(addr, (s1_len + 2), sizeof(char));
	if (!arr)
		return (NULL);
	ft_memmove(arr, dest, s1_len);
	ft_memmove(arr + s1_len, &c, 1);
	arr[s1_len + 1] = '\0';
	return (arr);
}
