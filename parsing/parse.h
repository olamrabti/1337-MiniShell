/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:38:54 by olamrabt          #+#    #+#             */
/*   Updated: 2024/03/03 18:35:04 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef enum token {
        W_SPACE = 255,
        _NL,
        RED_IN,
        RED_OUT,
        H_DOC_TRUNC,
        H_DOC_APPEND,
        _PIPE,
        _DOLLAR,
        D_QUOTE,
        S_QUOTE,
        _WORD,
        NULL_TOKEN,
} token;
    
typedef struct s_list
{
	char *value;
    token type;
	struct s_list	*prv;
	struct s_list	*nxt;
}	t_list;

char	*ft_strdup(const char *s);
char *ft_strndup(char *s, int n);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strcmp(const char *s1, const char *s2);
char *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_memmove(void *dst, const void *src, size_t len);
int ft_strlen(const char *s);
char *ft_getvalue(char *key, char **envp);
char *ft_expand_dollar(char *line, char **envp);
t_list *ms_tokenize(char *line, char **envp);
t_list	*create_node(char *value, token type);
int	node_addfront(t_list **list, t_list *new);
int	node_addback(t_list **list, t_list *new);
void	delete_node(t_list *node);
void	remove_list(t_list **list);


#endif