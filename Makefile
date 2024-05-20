# Variables

CC = cc

# CFLAGS = -Wall -Wextra -Werror -g

MAKE = make

SRC = $(addprefix sources/, hellGate.c lexer.c utils1.c lexer_utils.c pipe_checker.c parser.c extra_cases.c) \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/miniHell.h

READLINE_LIB = -lreadline

NAME = miniHell

LIBFT_AR = ./libft/libft.a

TOKEN = ghp_PcXPXcNDtE5TkUNF2s2kEcVhWCC9f0dZ33c

# Targets

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_AR)
		$(CC) $(CFLAGS)  $(OBJ) $(LIBFT_AR) $(READLINE_LIB) -o $(NAME)

$(LIBFT_AR):
		@$(MAKE) -C ./libft
		@echo "libft lib made"

clean:
		@rm -rf $(OBJ)
		@$(MAKE) clean -C ./libft
		@echo "Objects files removed"

fclean: clean
		@rm -rf $(NAME)
		@$(MAKE) fclean -C ./libft
		@echo "miniHell program destructed"
		@echo "libft archive cleaned"

re: fclean all

.phonix: clean fclean re all
