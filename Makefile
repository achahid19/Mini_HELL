# Variables

CC = cc

# CFLAGS = -Wall -Wextra -Werror

MAKE = make

SRC = $(addprefix sources/, hellGate.c expander.c lexer.c extra_cases.c pipe_checker.c parser.c) \
		$(addprefix sources/utils/, utils1.c lexer_utils.c expander_utils.c \
					expander_utils2.c) \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/miniHell.h

READLINE_LIB = -lreadline

NAME = miniHell

LIBFT_AR = ./libft/libft.a

# Targets

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_AR)
		$(CC) $(CFLAGS)  $(OBJ) $(READLINE_LIB) $(LIBFT_AR) -o $(NAME)

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
