/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:42:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/06/04 05:57:17 by oumimoun         ###   ########.fr       */
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
# include <limits.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/ioctl.h>
# include <dirent.h>

int	g_signal;

typedef enum token
{
	W_SPACE = 1,
	RED_IN,
	RED_OUT,
	R_O_APPEND,
	H_DOC,
	PIPE,
	_DOLLAR,
	Q_DOLLAR,
	D_QUOTE,
	S_QUOTE,
	WORD,
	NULL_TOKEN,
	RM,
	NF_VAR,
	LTRAL
}	t_token;

typedef struct s_list
{
	char			**args;
	char			*value;
	t_token			type;
	int				infile;
	int				outfile;
	int				first;
	int				last;
	int				herdoc;
	struct s_list	*prv;
	struct s_list	*nxt;

}	t_list;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;

}		t_env;

typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;

typedef struct s_data
{
	t_list						*cmd;
	pid_t						pid;
	int							*fds;
	int							save;
	int							pd[2];
	int							is_hiden;
	int							oldpwd;
	struct termios				*term;
	struct s_env				*env;
	struct s_addr				*addr;
	struct s_addr				*addr_env;
}	t_data;

int		ms_parse(t_data **data, char *line);
int		add_addr(t_addr **list, t_addr *new);
int		execute_commands(t_data **data);
int		ft_no_env(t_data **data);
int		ft_close_descriptors(t_data *data);
int		ft_exit_status(int status);
int		ft_exit_status(int status);

void	ft_free_env(t_env **envp);
void	init_data(int ac, char **av, t_data **data, char **envp);
void	ft_clean_parsing(t_data **data, char *line);
void	ctrl_c_handler(int signum);
void	ft_lstclear(t_addr **lst, void (*del)(void *));
void	ctrl_c_handler(int signum);

void	*ft_calloc(t_addr **addr, size_t count, size_t size);
char	*gc_strdup(const char *s, t_addr **addr);

t_env	*ft_parce_env(char **envp, t_addr **addr_env);
t_addr	*new_addr(char *value);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

#endif
