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

char *ft_charjoin(char *s1, char c)
{
	char *arr;
	char *dest;
	size_t s1_len;

	dest = s1;
	if (!s1)
	{
		arr = (char *)malloc(sizeof(char) * 2);
		if (!arr)
			return (NULL);
		arr[0] = c;
		arr[1] = '\0';
		return (arr);
	}
	s1_len = ft_strlen(dest);
	arr = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!arr)
		return (NULL);
	ft_memmove(arr, dest, s1_len);
	ft_memmove(arr + s1_len, &c, 1);
	arr[s1_len + 1] = '\0';
	return (arr);
}
