/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:41:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/06 11:54:53 by oumimoun         ###   ########.fr       */
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
        RED_OUT_APPEND,
        H_DOC,
        _PIPE,
        _DOLLAR,
        D_QUOTE,
        S_QUOTE,
        _WORD,
        NULL_TOKEN,
        _RM,
        NF_VAR,
        _LTRAL
} token;

typedef struct s_list
{
	char *value;
    char **args;
    int infile;
    int outfile;
    token type;
	struct s_list	*prv;
	struct s_list	*nxt;
    int first;
    int last;
    int herdoc;
}	t_list;

typedef struct s_env
{
    char *key;
    char *value;
    int is_null;
    struct s_env *next;

} t_env;

typedef struct s_data
{
    t_list *cmd;
    int status;
    int *fds;
    int save;
    pid_t pid;
    int pd[2];
    struct s_env *env;

} t_data;




////////////////////// parcing ////////////////////////////////


t_list *ms_tokenize(char *line);
int ms_parse(t_data **data, char *line, t_env *env);
void remove_list(t_list **list);
void print_list(t_list *list);





////////////////////// execution ////////////////////////////////


int execute_commands(t_data **data, char **envp);
t_env *ft_parce_env(char **envp);



#endif