#include "parse.h"
#include "../minishell.h"


int ft_isprint(int c)
{
    if (c >= 32 && c < 127)
        return (1);
    return (0);
}

int ft_isdigit(int d)
{
    if (d >= '0' && d <= '9')
        return (1);
    return (0);
}
int ft_isspace(int d)
{
    if (d == ' ' || (d >= 9 && d <= 13))
        return (1);
    return (0);
}
int ft_isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int ft_isalnum(int c)
{
    if (ft_isalpha(c) || ft_isdigit(c))
        return (1);
    return (0);
}