/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:14:27 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/18 08:46:16 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_list ft_fill_list(int ac, char **av)
{
    int i;
    t_list **list;
    i = 0;
    while (av[i])
    {
        ft_tokenize(list, av[i++]);
    }
    
}
char *ft_expand(char *str);

//NOTE ft_tokenize will be called for each node while filling the linked list.
void ft_tokenize(t_list **list, char *str)
{
    char *tmp;
    int i;
    
    tmp = str;
    i = 0;
    if (str[i] == '|')
    {
        if (str[i + 1] && *list)
            node_addback("|", _PIPE);
    }
    else if (str[i] == '$')
    {
        tmp = ft_expand(str);
        node_addback(tmp, _DOLLAR); 
    }
    else if (str[i] == '>')
        node_addback(">", RED_OUT);
    else if (str[i] == '<')
        node_addback("<", RED_IN);
    else if (str[i] == '>>')
        node_addback("<<", H_DOC_OUT);
    else if (str[i] == '<<')
        node_addback("<<", H_DOC_IN);
    else
        ft_store_word(); //stores the non special characters as _word token.
}