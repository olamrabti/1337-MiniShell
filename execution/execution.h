/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:24:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/25 16:21:21 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

# define SUCCESS 0
# define ERROR 1

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

// typedef struct s_env
// {
//     char *key;
//     char *value;
//     struct s_env *next;

// } t_env;


// void ft_putstr(char *str);
// void ft_putchar(char c);
// void ft_putendl(char *str);
// void ft_putnbr(int n);
// void ft_putendl_fd(char *str, int fd);
// void ft_putchar_fd(char c, int fd);
// void ft_putnbr_fd(int n, int fd);


void ft_putstr_fd(char *str, int fd);

int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, unsigned int n);
char *ft_strdup(char *str);
char	**ft_split(char const *s, char c, t_data *data);

char *ft_substr(char *s, unsigned int start, size_t len);
void *ft_memcpy(void *dest, const void *src, size_t n);


int execute_commands(t_data **data, char **envp);


int ft_execute_builtin(t_list *cmd, t_data *data);




char	*ft_strjoin(char *s1, char *s2);

char *ft_get_path(t_list *cmd, t_env *env, t_data *data);


char **ft_join_for_execve(t_list *cmd, t_addr *addr);

int ft_pipex(t_data *data, char **envp);



int ft_is_builtin(char *value);

int ft_cd(t_list *cmd, t_env **env, t_data *data);
int ft_pwd(t_list *cmd);
int ft_echo(t_list *cmd);
// int  ft_export(t_list * cmd, t_env **envp);

// void ft_print_export(t_env *envp);

int ft_change_env(char *str, t_env *envp, int concat, t_data *data);
int ft_unset(t_list *cmd, t_env **envp);
void ft_exit(t_list *cmd);

int	ft_isdigit(int d);
int	ft_isalpha(int c);
int	ft_isalnum(int c);

int *ft_alloc_tab(t_data *data, int *total);

int ft_close_descriptors(t_data *data);

int ft_no_env(t_data **data);


int ft_env(t_list *cmd, t_env **envp, t_data *data);
void ft_print_export(t_env **envp, int flag);

int ft_export(t_list *cmd, t_env **envp, t_data *data);

char    *ft_get_cwd(char *new_path, int mode);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t size);


int ft_execute(t_list *cmd, t_data *data, char **envp);

int ft_is_a_dir(char *str);

int ft_handle_dir(t_list *cmd, t_data *data, char **envp);


int	ft_atoi(char *str);

void ft_add_to_env(t_env **env, char *key, char *value);

// char *gc_substr(char *s, unsigned int start, size_t len, t_data *data);

#endif