/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:51:34 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/27 15:53:58 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
int		ft_isspace(int d);
int		ft_isdigit(int d);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		add_middle(t_list *curr, t_list *new);
int		addback(t_list **list, t_list *new);
int		delete_node(t_list *node);
int		check_syntax(t_list **list, int *count);
int		handle_quote(t_list **list, t_token quote, t_addr **addr);
int		get_key(char *line, int i, int j);
int		ms_parse(t_data **data, char *line, t_env *env);
int		fill_heredoc(t_list *deli, t_addr **addr, t_env *env);
int		is_after_red(t_list *curr, t_addr **addr, t_env *env);
int		fill_args(t_list *curr, int count, t_addr **addr);

void	expand_all(t_list **list, t_env *env, t_addr **addr);
void	empty_cmd(t_list *temp, t_addr **addr, t_env *env);
void	handle_args(t_list **list, t_addr **addr);
void	concat_words(t_list **list, t_addr **addr);
void	remove_token(t_list **list, t_token token);
void	ms_tokenize(t_list *current, char *line, t_addr **addr, int *j);
void	find_delimiter(t_list *list);

int		*handle_redirections(t_list **list, int *count, \
	t_data **data, t_env *env);
char	*ft_getvalue(char *key, t_env *env, t_addr **addr);
char	*gc_itoa(int n, t_addr **addr);
char	*ft_expand(char *line, t_env *env, t_addr **addr);
char	*gc_strdup(const char *s, t_addr **addr);
char	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strndup(char *s, int n, t_addr **addr);
char	*ft_charjoin(char *s1, char c, t_addr **addr);
char	*gc_strjoin(char *s1, char *s2, t_addr **addr);

char	**ft_split_sp(char const *s, t_addr **addr);

t_list	*handle_doubleq(t_list *curr, int *i, t_addr **addr);
t_list	*init_list(char *line, t_addr **addr);
t_list	*handle_singleq(t_list *curr, int *i, t_addr **addr);
t_list	*cr_node(char *value, t_token type, t_addr **addr);
t_list	*get_last_node(t_list *list);

#endif
