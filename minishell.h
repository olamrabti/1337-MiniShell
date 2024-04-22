/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:41:59 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/22 14:15:00 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
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
} token;

typedef struct s_list
{
	char *value;
    char *args;
    int infile; // open()... <
    int outfile; // open() when > >>(trunc)
    token type;
	struct s_list	*prv;
	struct s_list	*nxt;
}	t_list;

typedef struct s_data
{
    t_list *cmd;
    int status;
    int *fds;

} t_data;

////////////////////// parcing



t_list *ms_tokenize(char *line, char **envp);
void ms_parse(t_list **list, char **envp);
void remove_list(t_list **list);
void print_list(t_list *list);





////////////////////// execution


void execute_commands(t_data *data, char **envp);




#endif