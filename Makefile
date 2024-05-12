# Variables

CC = cc

# CFLAGS = -Wall -Wextra -Werror

MAKE = make

SRC = $(addprefix sources/, hellGate.c) \
	$(addprefix get_next_line/, get_next_line_bonus.c get_next_line_utils.c) \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/miniHell.h

READLINE_LIB = -lreadline # should install readline library "https://ftp.gnu.org/gnu/readline/" v8.1.2

NAME = miniHell

LIBFT_AR = ./libft/libft.a

TOKEN = ghp_PcXPXcNDtE5TkUNF2s2kEcVhWCC9f0dZ33c

# Targets

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_AR)
		$(CC) $(CFLAGS) $(READLINE_LIB) $(LIBFT_AR) $(OBJ) -o $(NAME)

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
