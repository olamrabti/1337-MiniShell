/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:07:01 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/23 11:18:04 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    int i;
    char *p;

    i = 0;
    p = (char *)malloc(ft_strlen(str) + 1 * sizeof(char));
    if (p == NULL)
        return (NULL);
    while (str[i] != '\0')
    {
        p[i] = str[i];
        i++;
    }
    p[i] = '\0';
    return (p);
}

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
    unsigned int i;

    i = 0;
    while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
    {
        if (s1[i] != s2[i])
            return ((unsigned char)(s1[i]) - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char *result;

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

