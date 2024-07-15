/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniHell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:31:11 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/15 18:17:59 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H
# include <signal.h> // for handling signals
# include <stdio.h> // for debugging
# include <unistd.h> // write ...
# include <limits.h> // INT_MAX ...
# include <stdlib.h> // malloc, free ...
# include <termios.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <fcntl.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// define a set of named integer constant
typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	whitespace_token = 0,
	pipe_token = 1,
	word_token = 2,
	string_token = 3,
	singlequote_token = 4,
	doublequote_token = 5,
	rbracket_token = 6,
	lbracket_token = 7,
	leftred_token = 8,
	rightred_token = 9,
	heredoc_token = 10,
	append_token = 11,
	filename_token = 20,
	cmd = 12
}	t_type;

/**
 * I know u for compiler
*/
typedef struct s_token	t_token;
typedef t_token			*token_ptr;

// lexer: token's data
typedef struct s_token
{
	char		*token;
	int			order; // index of the token on the input
	t_type		token_type; // define a type of each encoutred token
	int			token_length;
	token_ptr	next;
	token_ptr	previous;
}   t_token;

/**
 * struct for data expander
*/
typedef struct s_expand
{
	int 	new_tk_len;
	char	*new_token;
	int		dollar_tk_len;
	int		tmp_tk_len;
	size_t	i;
	/* tokens_expander data */
	char	*ptr_token;
	char	*dollar_tk;
	int		tmp_dollar_len;
	int		dollars_count;
	t_bool	flag;
}	t_expand;

typedef struct s_var
{
	/* lexer data */
	token_ptr	tk_head;
	int			o;
	int			type;
	t_bool		s;
	char		*temp;
	int			type_count;
	int			o_type;
	t_bool		space;
	/* */
	char	**token;
	char	**path;
	char	*path_to_cmd;
	char	*env;
	size_t	i;
	/* for quotes_handler */
	int			type_next;
	int			type_previous;
	int			type_next_next;
	t_bool		is_space;
	token_ptr	tmp;
	/* executor's data */
	token_ptr	head;
	token_ptr	tokens_list;
	char		**envp;
	char		*user_input;
	int			pipes;
	int			std_in;
	int			fd[2];
	/* pipe data */
	pid_t	child_pid;
	int		end[2];
}	t_var;

/* Lexical analyzer */
token_ptr	lexer(char *user_input);
t_bool		string_tokens(char **user_input, token_ptr *tokens_head,
							int type, int *order);
t_bool		char_tokens(char **user_input, token_ptr *tokens_head,
							int type, int order);

/* Lexer utils */
t_bool		token_create(char **user_input, token_ptr *tokens_head,
							int type, int order);
int			get_token_length(char *user_input, int type, token_ptr tokens_head);
char		*get_token(char *user_input, int token_len);
int			get_type(char user_input);
void		move_user_input(char **user_input);

/* utilities */
token_ptr	find_last_node(token_ptr head);
t_bool		ft_isspace(char c);
char		*ft_realloc(char *to_free, int new_len);
void		dup_and_close(int *end, int i);
void		points_checker(t_var data, char **av);

/* expander */
void		tokens_expander(token_ptr tokens_list, char **envp);
char		*extract_dollar_token(char *ptr_token, char *dollar_tk,
				int dollar_tk_len);
char		*get_value(char *dollar_tk, int *dtk_len, char **envp);
char		*expanding(char *dollar_tk, char *token, int tmp_tk_len);
void		move_data(t_expand *data, char *dollar_tk, char *token);


/* expander utils */
char		*find_dollar(char *ptr_token);
void	  	check_expander_chars(t_expand *d);
int			get_variable_len(char *envp);
char		*retrieve_value(char *envp, char *dollar_tk);
t_bool		check_type(int token_type);

/* expander utils2 */
void		tokens_expander_helper(token_ptr tokens_list, char **envp,
				t_expand d);
int			dollars_count(char *token);
int			get_biggest_len(char *envp, char *dollar_tk);
void		data_move_helper(t_expand *data, char **token);

/* expander utils3 */
t_bool		string_handler(token_ptr *tokens_list);
t_bool		doublequote_handler(token_ptr *tokens_list);
t_bool		singlequote_handler(token_ptr *tokens_list);

/* Parser */
int			parser_tokens(token_ptr tokens_list, t_env *env);
int			pipe_checker(token_ptr tokens_list);
int			redirections_checker(token_ptr tokens_list);
int			semicolon_checker(token_ptr tokens_list);
int			backslash_checker(token_ptr tokens_list);
void		built_in(token_ptr tokens_list);
int			parentheses_checker(token_ptr tokens_list);
int			parser_tokens_2(token_ptr tokens_list);
int			heredoc_next_checker(token_ptr tokens_list);
int			heredoc_append_checker(token_ptr tokens_list);
void		space_skip(token_ptr tokens_list);
void		space_skip_rev(token_ptr tokens_list);
char		*get_unique_filename(int i);
void		new_token_lst(token_ptr tokens_list, int order);
void		filename_write(token_ptr tokens_list, char *filename, int order);
void		heredoc(token_ptr tmp, token_ptr tokens_list, t_env *envp);
char		*ft_expand_heredoc(char *line, t_env *envp);
char		*ft_delimiter(token_ptr tokens_list, int order);
char		**ft_advanced_split(const char *str);
t_env		*init_env(char** env);

/* built_in   	*/
void		ft_echo(token_ptr tokens_list);

/* signal handler */
void		handler(int signum);
void		signal_handler();

/* free_and_errors */
void		free_tokens(token_ptr tokens_list);
void		free_all(token_ptr tokens_list, char *user_input, char **av);
void		free_cmd_table(char **full_cmd);
void		quotes_error(int quotes_type);
void		print_error(char *error);
void		exit_error(char *error, t_var *data, char **av, int exit_code);

/* utils2 */
void		tokens_order(token_ptr tokens_list);
token_ptr	get_next_pipe(token_ptr tokens_list);
void		get_next_type(token_ptr *tokens_list, t_var d);
t_bool		special_chars_checker(int type);
t_bool		quotes_cmd_checker(t_var d);

/* syntax_builder */
void		syntax_algo(token_ptr tokens_list);
void		check_no_cmd(token_ptr tokens_list);

/* syntax builder utils */
int			check_pipes_num(token_ptr tokens_list);
void		same_type_finder(token_ptr *tokens_list);
t_bool		type_checker(int type);
t_bool		cmd_checker(token_ptr tokens_list);
void		quotes_handler_helper(token_ptr tokens_list, t_var d);

/* syntax builder utils 2 */
t_bool		handle_qt(token_ptr	*tokens_list, t_var d);
void		words_finder(token_ptr *tokens_list, t_var d);
t_bool		tmp_checker(token_ptr *tokens_list, token_ptr tmp, t_bool *status);
t_bool		multiple_quotes_check(t_var d, token_ptr tmp);
t_bool		types_checker(t_var d, int index, token_ptr tmp);

/* tokens checker (printed on terminal) */
void		check_tokens(token_ptr print_tk);

/* executor */
void		executor(token_ptr tokens_list, char **env, char *user_input);

/* tk_optimizer */
void		tokens_list_optimizer(token_ptr *tokens_list);
void 		special_chars_refactor(token_ptr tokens_list);
void 		node_remover(token_ptr *node);
t_bool		special_chars_finder(token_ptr *tokens_list, token_ptr node_add,
				int type);

/* exucutor uitls */
t_bool		extract_cmd_helper(token_ptr *tokens_list,
					int *i, char **full_cmd);
t_bool		get_infos_helper(token_ptr *tokens_list,
					t_bool *flag, int *rows);

/* pipes uitls */
void		child_exec_cmd(char **av, t_var *data, t_bool pipe_switcher);
void		dup_and_close(int *end, int i);
char		*ft_cmd_path(char *cmd_path);
char		*ft_get_path(char **envp);
char		*ft_find_cmd(char *cmd, char **envp);

/* IO_stream */
t_bool		input_red_stream(t_var *data);
t_bool		input_red_fd(token_ptr *temp, t_var *data);
void		output_red_stream(t_var *data);
void		output_red_fd(token_ptr *temp, t_var *data);

/* status_utils */
void		dollar_status_check(token_ptr tokens_list);
char		*expand_status(char *tk, int *i);
int			get_length(char *tk);
void		before_tk_status(char *before, char *tk);
void		after_tk_status(char *after, char *tk);

/* utils 3*/
t_bool		check_single_quotes(token_ptr node);
t_bool		builtin_checker(char *built_in);
void		open_output_fd(token_ptr *temp, t_var *data);
t_bool		check_quotes(t_var *d, token_ptr *tokens_list);
t_bool		space_trim(token_ptr tokens_list);

/* utils 4 */
void		quotes_substitut(char **cmd_table);

#endif /* MINIHELL_H */
