
#ifndef PARSE_H
# define PARSE_H

#include "../minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>




char    *gc_strdup(const char *s, t_addr **addr);
char *ft_strndup(char *s, int n, t_addr **addr);
char *ft_charjoin(char *s1, char c, t_addr **addr);
char *gc_strjoin(char *s1, char *s2, t_addr **addr);
char    *ft_memcpy(void *dst, const void *src, size_t n);
char    *ft_memmove(void *dst, const void *src, size_t len);
int     ft_strcmp(const char *s1, const char *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strlen(const char *s);
int     ft_isspace(int d);
int     ft_isdigit(int d);
int     ft_isalpha(int c);
int     ft_isalnum(int c);
int     ft_isprint(int c);
char    **ft_split_sp(char const *s, t_addr **addr);

char    *ft_getvalue(char *key, t_env *env , t_addr **addr);
char    *ft_expand(char *line, t_env *env, t_addr **addr);
void expand_all(t_list **list, t_env *env, t_addr **addr);
int     get_key(char *line, int i, int j);
int handle_quote(t_list **list, token quote,t_addr **addr);
t_list *handle_singleq(t_list *curr, int *i, t_addr **addr);
t_list *handle_doubleq(t_list *curr, int *i, t_addr **addr);

t_list *ms_tokenize(char *line, t_addr **addr);
int ms_parse(t_data **data, char *line, t_env *env);

int *handle_redirections(t_list **list, int *count, t_addr **addr);
int is_valid_name(char *str);

int open_heredoc(int tmp , t_addr **addr);
int fill_heredoc(int tmp, char *deli, t_addr **addr);

t_list	*create_node(char *value, token type, t_addr **addr);
int	node_addfront(t_list **list, t_list *new);
int node_add_middle(t_list *curr, t_list *new);
int	node_addback(t_list **list, t_list *new);
int	delete_node(t_list *node);
void remove_list(t_list **list);
void remove_token(t_list **list, token token);
void print_list(t_list *list);
t_list *get_last_node(t_list *list);




#endif