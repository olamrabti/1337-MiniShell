/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:07:01 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/25 15:01:35 by oumimoun         ###   ########.fr       */
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s) || !len)
		return (ft_strdup(""));
	if (len + start > (unsigned int)ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s + start, len);
	result[len] = '\0';
	return (result);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    char *byte_dest;
    char *byte_src;

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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s2) + ft_strlen(s1);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		result[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	result[i + ft_strlen(s1)] = '\0';
	return (result);
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
