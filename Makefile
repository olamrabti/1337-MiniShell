
CC = cc

CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

SRCS = parsing/linked_list_utils.c parsing/ms_parse.c parsing/ms_tokenize.c parsing/ft_strcmp.c \
 parsing/ft_strjoin.c parsing/ft_strdup.c main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all