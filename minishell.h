
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
#include <signal.h>


typedef enum token {
        W_SPACE = 1,
        RED_IN,
        RED_OUT, 
        RED_OUT_APPEND, 
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
    struct s_env *next;

} t_env;

typedef struct s_addr
{
    void *address;
    struct s_addr *nxt;
} t_addr;

typedef struct s_data
{
    t_list *cmd;
    int *fds;
    int save;
    pid_t pid;
    int pd[2];
    int is_hiden;
    int oldpwd;
    struct s_env *env;
    struct s_addr *addr;

} t_data;




////////////////////// parcing ////////////////////////////////


// t_list *ms_tokenize(char *line, t_addr **addr);
int ms_parse(t_data **data, char *line, t_env *env);
void remove_list(t_list **list);
void print_list(t_list *list);



void	*ft_calloc(t_addr **addr, size_t count, size_t size);
int	add_addr(t_addr **list, t_addr *new);
t_addr	*new_addr(char *value);
int	delete_addr(t_addr *node);
void    clean_all(t_addr **list);
void print_addr(t_addr *list);
// void	ft_lstiter(t_addr *lst, void (*f)(void *));
void	ft_lstclear(t_addr **lst, void (*del)(void *));




////////////////////// execution ////////////////////////////////


int execute_commands(t_data **data, char **envp);
t_env *ft_parce_env(char **envp);

char *gc_strdup(const char *s, t_addr **addr);

int ft_no_env(t_data **data);

int ft_close_descriptors(t_data *data);

int ft_exit_status(int status);

int ft_is_a_dir(char *str);
int ft_handle_dir(char *str);


#endif