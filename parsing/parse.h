/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:38:54 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/06 14:13:35 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>



char	*ft_strdup(const char *s);
char *ft_strndup(char *s, int n);
char	*ft_strjoin(char *s1, char *s2);
char *ft_charjoin(char *s1, char c);
int	ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_memmove(void *dst, const void *src, size_t len);
int ft_strlen(const char *s);
int	ft_isspace(int d);
int	ft_isdigit(int d);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_isprint(int c);
char	**ft_split_sp(char const *s);

char *ft_getvalue(char *key, t_env *env);
char *ft_expand(char *line, t_env *env);
void expand_all(t_list **list, t_env *env);
int get_key(char *line, int i, int j);

int handle_quote(t_list **list, token quote);
t_list *handle_singleq(t_list *curr, int *i);
t_list *handle_doubleq(t_list *curr, int *i);

t_list *ms_tokenize(char *line);
int ms_parse(t_data **data, char *line, t_env *env);

int *handle_redirections(t_list **list, int *count);
int is_valid_name(char *str);

int open_heredoc(int tmp);
int fill_heredoc(int tmp, char *deli);

t_list	*create_node(char *value, token type);
int	node_addfront(t_list **list, t_list *new);
int node_add_middle(t_list *curr, t_list *new);
int	node_addback(t_list **list, t_list *new);
int	delete_node(t_list *node);
void remove_list(t_list **list);
void remove_token(t_list **list, token token);
void print_list(t_list *list);
t_list *get_last_node(t_list *list);



#endif