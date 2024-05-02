/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:41:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/02 16:30:42 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "execution/execution.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum token {
        W_SPACE = 1,
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
        _RM
} token;

typedef struct s_list
{
	char *value;
    char **args;
    int infile; // open()... <
    int outfile; // open() when > >> (trunc) 
    token type;
	struct s_list	*prv;
	struct s_list	*nxt;
    int first;
    int last;
}	t_list;

typedef struct s_data
{
    t_list *cmd;
    int status;
    int *fds;
    int save;
    pid_t pid;
    int pd[2];

} t_data;

////////////////////// parcing ////////////////////////////////

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;

} t_env;


t_list *ms_tokenize(char *line, char **envp);
int ms_parse(t_data **data, char *line, char **envp);
void remove_list(t_list **list);
void print_list(t_list *list);





////////////////////// execution ////////////////////////////////


int execute_commands(t_data **data, t_env *env);
t_env *ft_parce_env(char **envp);



#endif