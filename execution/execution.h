/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:24:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/23 13:59:16 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

typedef struct s_env
{
    char *key;
    char *value;
    char **path;
    struct s_env *next;
} t_env;


// void ft_putstr(char *str);
// void ft_putchar(char c);
// void ft_putendl(char *str);
// void ft_putnbr(int n);
// void ft_putendl_fd(char *str, int fd);
void ft_putstr_fd(char *str, int fd);
// void ft_putchar_fd(char c, int fd);
// void ft_putnbr_fd(int n, int fd);

int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, unsigned int n);
char *ft_strdup(char *str);
char	**ft_split(char const *s, char c);
char *ft_substr(char *s, unsigned int start, size_t len);
void *ft_memcpy(void *dest, const void *src, size_t n);

void ft_env(char **envp);
int execute_commands(t_data *data, char **envp);
void ft_add_to_env(t_env **env, char *key, char *value);
void ft_execute_builtin(char *cmd, t_env *env);

void ft_add_to_env(t_env **env, char *key, char *value);
t_env *ft_parce_env(char **envp);
int ft_is_one_cmd(t_data *data);
int execute_one_command(t_list *cmd, t_env *env);
void ft_fill_path(t_env *env);

char	*ft_strjoin(char *s1, char *s2);

char *ft_get_path(t_list *cmd, t_env *env);


char **ft_join_for_execve(t_list *cmd);





#endif