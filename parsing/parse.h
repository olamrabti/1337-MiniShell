/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:38:54 by olamrabt          #+#    #+#             */
/*   Updated: 2024/04/26 11:44:29 by oumimoun         ###   ########.fr       */
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
char *ft_getvalue(char *key, char **envp);
char *ft_expand(char *line, char **envp);
t_list *ms_tokenize(char *line, char **envp);
int ms_parse(t_data **data, char *line, char **envp);
t_list	*create_node(char *value, token type);
int	node_addfront(t_list **list, t_list *new);
int	node_addback(t_list **list, t_list *new);
int	delete_node(t_list *node);
void	remove_list(t_list **list);
void print_list(t_list *list);
t_list *get_last_node(t_list *list);


int	ft_isspace(int d);
int	ft_isdigit(int d);
int	ft_isalpha(int c);
int	ft_isalnum(int c);

#endif