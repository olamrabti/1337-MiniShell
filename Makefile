CC = cc

CFLAGS = -Wall -Wextra -Werror -g 

NAME = minishell

SRCS = main.c \
	parsing/linked_list_utils.c \
	parsing/ms_parse.c \
	parsing/ms_tokenize.c \
	parsing/ft_strcmp.c \
	parsing/ft_strjoin.c \
	parsing/ft_strdup.c \
	execution/execution.c \
	execution/execution_utils.c \
	execution/pipex.c \
	execution/one_cmd.c \
	execution/helpers.c \
	execution/parce_env.c \
	execution/ft_split.c \
	execution/ft_init_cmds.c \
	execution/cd.c \
	execution/pwd.c \
	# execution/echo.c \
	# execution/exit.c \
	# execution/export.c \
	# execution/unset.c \
	# execution/env.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all