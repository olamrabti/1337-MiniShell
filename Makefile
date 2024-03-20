
CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRCS = parsing/linked_list_utils.c parsing/ms_parse.c parsing/ms_tokenize.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all