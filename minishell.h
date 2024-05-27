
#ifndef MINISHELL_H
# define MINISHELL_H

#define BOLD_WHITE "\033[1;37m"
#define RESET "\033[0m"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <dirent.h>


int global_signal;


typedef enum token {
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
    struct termios *term;
    struct s_env *env;
    struct s_addr *addr;
    struct s_addr *addr_env;

} t_data;




////////////////////// parcing ////////////////////////////////

int ms_parse(t_data **data, char *line, t_env *env);

// NOTE delete me before push 
void print_list(t_list *list);



////////////////////// gc ////////////////////////////////

void	*ft_calloc(t_addr **addr, size_t count, size_t size);
t_addr	*new_addr(char *value);
int	add_addr(t_addr **list, t_addr *new);
void	ft_lstclear(t_addr **lst, void (*del)(void *));




////////////////////// execution ////////////////////////////////


int execute_commands(t_data **data, char **envp);
t_env *ft_parce_env(char **envp, t_addr **addr_env);

char *gc_strdup(const char *s, t_addr **addr);

int ft_no_env(t_data **data);

int ft_close_descriptors(t_data *data);

int ft_exit_status(int status);


void ctrl_c_handler(int signum);

size_t ft_strlcpy(char *dest, const char *src, size_t size);

#endif