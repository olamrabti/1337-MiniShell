/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:07:01 by oumimoun          #+#    #+#             */
/*   Updated: 2024/06/04 05:48:05 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lsrc;
	unsigned int	ldest;

	if (!dest && !size)
		return (0);
	ldest = ft_strlen(dest);
	lsrc = ft_strlen(src);
	i = 0;
	j = ldest;
	if (size == 0 || size <= ldest)
		return (lsrc + size);
	while (src[i] && i < (size - 1) - ldest)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (lsrc + ldest);
}

char	*gc_substr(char *s, unsigned int start, size_t len, t_addr **addr)
{
	char	*result;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s) || !len)
		return (gc_strdup("", addr));
	if (len + start > (unsigned int)ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	result = (char *)ft_calloc(addr, (len + 1), sizeof(char));
	if (!result)
		exit(1);
	ft_memcpy(result, s + start, len);
	result[len] = '\0';
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*byte_dest;
	char	*byte_src;

	if (!src && !dest)
		return (NULL);
	if (src == dest)
		return (dest);
	i = 0;
	byte_dest = (char *)dest;
	byte_src = (char *)src;
	while (i < n)
	{
		byte_dest[i] = byte_src[i];
		i++;
	}
	return (byte_dest);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
