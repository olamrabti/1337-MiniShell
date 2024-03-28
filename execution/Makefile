# **************************************************************************** #
# VARIABLES

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
HEADER	:= minishell.h

# **************************************************************************** #
# COLORS

GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
END_COLOR	= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC = execution.c \
	  execution_utils.c \
	  


OBJ = $(SRC:.c=.o)

# **************************************************************************** #
# RULES

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $<
	@echo "$(BLUE)Compiling $(notdir $<)$(END_COLOR)"

clean:
	@rm -rf $(OBJ)
	@echo "$(YELLOW)$(NAME) object & dependency files cleaned.$(END_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) executable file cleaned.$(END_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned all and rebuilt $(NAME)!$(END_COLOR)"

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re