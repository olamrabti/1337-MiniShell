/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:41:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/01 12:24:16 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
        NF_VAR
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



t_list *ms_tokenize(char *line, char **envp);
int ms_parse(t_data **data, char *line, char **envp);
void remove_list(t_list **list);
void print_list(t_list *list);





////////////////////// execution ////////////////////////////////


int execute_commands(t_data **data, char **envp);




#endif