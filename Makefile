CC = cc

CFLAGS = -Wall -Wextra -Werror -g  

NAME = minishell

SRCS = main.c \
	parsing/linked_list_utils.c \
	parsing/ms_parse.c \
	parsing/here_doc.c \
	parsing/quotes.c \
	parsing/expand.c \
	parsing/redirections.c \
	parsing/ms_tokenize.c \
	parsing/ft_strcmp.c \
	parsing/ft_split_sp.c \
	parsing/ft_strjoin.c \
	parsing/ft_strdup.c \
	execution/execution.c \
	execution/execution_utils.c \
	execution/pipex.c \
	execution/one_cmd.c \
	execution/helpers.c \
	execution/parce_env.c \
	execution/ft_split.c \
	execution/cd.c \
	execution/pwd.c \
	execution/env.c \
	execution/echo.c \
	execution/export.c \
	execution/unset.c \
	# execution/exit.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all