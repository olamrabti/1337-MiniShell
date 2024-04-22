/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:24:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/22 14:00:44 by oumimoun         ###   ########.fr       */
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
void execute_commands(t_data *data, char **envp);

#endif