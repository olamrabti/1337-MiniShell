/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:24:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/21 15:49:24 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

#include <stdio.h>                  // printf, perror
#include <stdlib.h>                 // malloc, free, exit, getenv
#include <unistd.h>                 // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
#include <fcntl.h>                  // open
#include <sys/wait.h>               // wait, waitpid, wait3, wait4
#include <string.h>                 // strerror

typedef struct s_data
{
    char *cmd;
    char *args;
    int infile;
    int outfile;
    struct s_data *next;
    struct s_data *prev;
} t_data;

typedef enum token
{
    W_SPACE = 255,
    _NL,
    RED_IN,
    RED_OUT,
    H_DOC_IN,
    H_DOC_OUT,
    _PIPE,
    _DOLLAR,
    D_QUOTE,
    S_QUOTE,
    _WORD
} token;

typedef struct s_env
{
    char *key;
    char *value;
    char *env;
    struct s_env *next;
} t_env;



void ft_putstr(char *str);
void ft_putchar(char c);
void ft_putendl(char *str);
void ft_putnbr(int n);
void ft_putendl_fd(char *str, int fd);
void ft_putstr_fd(char *str, int fd);
void ft_putchar_fd(char c, int fd);
void ft_putnbr_fd(int n, int fd);

int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, unsigned int n);
char *ft_strdup(char *str);
char	**ft_split(char const *s, char c);

void ft_env(char **envp);

#endif