/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:35 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/17 11:49:26 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char *ft_memmove(void *dst, const void *src, size_t len)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	char	*dest;
	char	*src;
	size_t	s1_len;
	size_t	s2_len;

	dest = (char *)s1;
	src = (char *)s2;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(dest);
	s2_len = ft_strlen(src);
	arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!arr)
		return (NULL);
	ft_memmove(arr, dest, s1_len);
	ft_memmove(arr + s1_len, src, s2_len);
	arr[s1_len + s2_len] = '\0';
	return (arr);
}
