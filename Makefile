# Variables

# ANSI escape codes for colors
RED = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

CC = cc

# CFLAGS = -Wall -Wextra -Werror

MAKE = make

SRC =   $(addprefix sources/parsing/, pipe_checker.c parser.c redirection.c extra_parse.c heredoc_checker.c echo.c heredoc_executor.c heredoc_executor_helper.c) \
    	$(addprefix sources/, hellGate.c expander.c lexer.c signals.c syntax_builder.c executor.c) \
		$(addprefix sources/utils/, expander_utils2.c utils1.c lexer_utils.c expander_utils.c \
					utils2.c expander_utils3.c tk_optimizer.c syntax_builder_utils.c \
					syntax_builder_utils2.c executor_utils.c pipe_utils.c io_stream.c global.c \
					status_utils.c utils3.c utils4.c) \
		$(addprefix sources/free_and_errors/, free.c erros.c)

# valgrind --leak-check=full --show-leak-kinds=all --suppressions=.readline.supp ./miniHell

OBJ_DIR = garbage_objs

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

INCLUDES = includes/miniHell.h

READLINE_LIB = -lreadline

NAME = minishell

LIBFT_AR = ./libft/libft.a

# Targets

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_AR)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_LIB) $(LIBFT_AR) -o $(NAME)
	@printf "\n"
	@printf $(RED)
	@printf "███╗░░░███╗██╗███╗░░██╗██╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n"
	@printf "████╗░████║██║████╗░██║██║██║░░██║██╔════╝██║░░░░░██║░░░░░\n"
	@printf "██╔████╔██║██║██╔██╗██║██║███████║█████╗░░██║░░░░░██║░░░░░\n"
	@printf "██║╚██╔╝██║██║██║╚████║██║██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n"
	@printf "██║░╚═╝░██║██║██║░╚███║██║██║░░██║███████╗███████╗███████╗\n"
	@printf "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n"
	@printf $(GREEN)
	@printf "	     　 ▒█▀▀█ █▀▀ █▀▀█ █▀▀▄ █░░█\n"
	@printf "	     　 ▒█▄▄▀ █▀▀ █▄▄█ █░░█ █▄▄█\n"
	@printf "	     　 ▒█░▒█ ▀▀▀ ▀░░▀ ▀▀▀░ ▄▄▄█\n"
	@printf $(RESET)

$(OBJ_DIR)/%.o: sources/parsing/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: sources/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: sources/utils/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: sources/free_and_errors/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_AR):
	@$(MAKE) -C ./libft
	@echo "libft lib made"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C ./libft
	@echo "Objs files removed"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C ./libft
	@echo "miniHell program destructed"
	@echo "libft archive cleaned"

re: fclean all

.PHONY: clean fclean re all
