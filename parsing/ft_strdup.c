/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:32 by olamrabt          #+#    #+#             */
/*   Updated: 2023/10/31 13:52:32 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
int ft_strlen(const char *s)
{
	if(!s || !*s)
		return 0;
	return (ft_strlen(s + 1) + 1);
}



char	*ft_strdup(const char *s)
{
	char	*copy;

	if (!s[0])
	{
		copy = (char *)malloc(sizeof(char));
		if (!copy)
			return (NULL);
		copy[0] = '\0';
		return (copy);
	}
	copy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, ft_strlen(s));
	copy[ft_strlen(s)] = '\0';
	return (copy);
}

char *ft_strndup(char *s, int n)
{
    char *copy;
    int i;

	if (!s)
		return (NULL);
    copy = malloc(n + 1);
    if (!copy)
        return (NULL);
    i = 0;
    copy[n] = '\0';
    while (i < n)
    {
        copy[i] = s[i];
        i++;
    }
    return (copy);
}
