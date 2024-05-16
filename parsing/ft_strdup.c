
#include "parse.h"

int ft_strlen(const char *s)
{
	if (!s)
		return 0;
	if (!*s)
       return 0;
	return (ft_strlen(s + 1) + 1);
}

char *gc_strdup(const char *s, t_addr **addr)
{
	char *copy;

	if (!s[0])
	{
		copy = (char *)ft_calloc(addr, 1, sizeof(char));
		if (!copy)
			return (NULL);
		copy[0] = '\0';
		return (copy);
	}
	copy = (char *)ft_calloc(addr, (ft_strlen(s) + 1) , sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, ft_strlen(s));
	copy[ft_strlen(s)] = '\0';
	return (copy);
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

// char	*ft_strdup(const char *str)
// {
// 	int		i;
// 	char	*p;

// 	i = 0;
// 	p = (char *)malloc(ft_strlen(str) + 1 * sizeof(char));
// 	if (p == NULL)
// 		return (NULL);
// 	while (str[i] != '\0')
// 	{
// 		p[i] = str[i];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

char *ft_strndup(char *s, int n, t_addr **addr)
{
	char *copy;
	int i;

	if (!s)
		return (NULL);
	copy = ft_calloc(addr, n + 1, sizeof(char));
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
