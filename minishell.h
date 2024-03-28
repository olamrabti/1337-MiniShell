/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:52:40 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/28 06:00:05 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <readline/readline.h>     // readline
#include <readline/history.h>      // rl_clear_history, add_history
#include <stdio.h>                  // printf, perror
#include <stdlib.h>                 // malloc, free, exit, getenv
#include <unistd.h>                 // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
#include <fcntl.h>                  // open
#include <sys/wait.h>               // wait, waitpid, wait3, wait4
#include <signal.h>                 // signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>               // stat, lstat, fstat
#include <dirent.h>                 // opendir, readdir, closedir
#include <string.h>                 // strerror
#include <termios.h>                // tcsetattr, tcgetattr
#include <sys/ioctl.h>              // ioctl
#include <curses.h>                 // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs


#define PROMPT "minishell$ "

#define BUILTINS "echo cd pwd export unset env exit"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"


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

typedef struct s_list
{
    char *value;
    token type;
    struct s_list *prv;
    struct s_list *nxt;
} t_list;

typedef struct s_env
{
    char *key;
    char *value;
} t_env;

typedef struct s_cmd
{
    char **av;
    char *cmd;
    int pipe;
    int redir;
    int redir_type;
    char *redir_file;
    struct s_cmd *next;
} t_cmd;

typedef struct s_shell
{
    t_env *env;
    t_cmd *cmd;
    int status;
} t_shell;



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
int ft_strncmp(char *s1, char *s2, int n);
char *ft_strdup(char *str);

#endif
