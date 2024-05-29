CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = minishell

SRCS = main.c \
	parsing/address_collector.c \
	parsing/address_collector_utils.c \
	parsing/arguments.c \
	parsing/expand.c \
	parsing/expand_utils.c \
	parsing/linked_list_utils.c \
	parsing/ms_parse.c \
	parsing/here_doc.c \
	parsing/quotes.c \
	parsing/redirections.c \
	parsing/ms_tokenize.c \
	parsing/syntax_utils.c \
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
	execution/exit.c \
	execution/handle_no_env.c \
	execution/handle_dir.c \
	execution/export_utils.c \
	execution/export_helpers.c \
	execution/ft_get_paths.c \
	execution/pipex_helpers.c \
	execution/pipex_utils.c \
	execution/utils.c \
	execution/ft_not_a_dir.c \

brew = $(shell brew --prefix readline)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

OBJS = $(SRCS:.c=.o)

all:
	@$(MAKE) $(NAME)

$(NAME) : $(OBJS) 
	@echo "$(GREEN)Creating MINISHELL...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L $(brew)/lib

%.o: %.c minishell.h parsing/parse.h execution/execution.h
	@$(CC) $(CFLAGS)  -c $< -I $(brew)/include -o $@

clean :
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)

fclean : clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

re : fclean all
