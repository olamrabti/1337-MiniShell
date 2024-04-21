
CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

SRCS = parsing/linked_list_utils.c parsing/ms_parse.c parsing/ms_tokenize.c parsing/ft_strcmp.c \
 parsing/ft_strjoin.c parsing/ft_strdup.c main.c \
#  execute/execute.c execute/ft_cd.c execute/ft_echo.c execute/ft_env.c execute/ft_exit.c \
#  execute/ft_export.c execute/ft_pwd.c execute/ft_unset.c execute/ft_execve.c execute/ft_pipe.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all