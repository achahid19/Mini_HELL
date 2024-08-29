/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniHell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:31:11 by achahid-          #+#    #+#             */
/*   Updated: 2024/08/29 01:40:09 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H
# include "../libft/libft.h"
# include "global.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h> // INT_MAX ...
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // for handling signals
# include <stdio.h>  // for debugging
# include <stdlib.h> // malloc, free ...
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h> // write ...
# include <sys/stat.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// define a set of named integer constant
typedef enum e_bool
{
	false = 0,
	true = 1
}						t_bool;

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
	filename_tk = 21,
	cmd = 12
}						t_type;

/**
 * I know u for compiler
*/
typedef struct s_token	t_token;
typedef t_token			*t_ptr;

// lexer: token's data
typedef struct s_token
{
	char	*token;
	int		order;
	t_type	token_type;
	int		token_length;
	t_ptr	next;
	t_ptr	previous;
}	t_token;

/**
 * struct for data expander
*/
typedef struct s_expand
{
	int					new_tk_len;
	char				*new_token;
	int					dollar_tk_len;
	int					tmp_tk_len;
	size_t				i;
	/* tokens_expander data */
	char				*ptr_token;
	char				*dollar_tk;
	int					tmp_dollar_len;
	int					dollars_count;
	t_bool				flag;
}						t_expand;

typedef struct s_var
{
	/* lexer data */
	t_ptr			tk_head;
	int				o;
	int				type;
	t_bool			s;
	char			*temp;
	int				type_count;
	int				o_type;
	t_bool			space;
	/* */
	char			**token;
	char			**path;
	char			*path_to_cmd;
	char			*env;
	size_t			i;
	/* for quotes_handler */
	int				type_next;
	int				type_previous;
	int				type_next_next;
	t_bool			is_space;
	t_ptr			tmp;
	/* executor's data */
	t_ptr			head;
	t_ptr			tokens_list;
	char			**envp;
	char			*user_input;
	int				pipes;
	int				std_in;
	int				fd[2];
	/* pipe data */
	pid_t			child_pid;
	int				end[2];
	/* transform envp */
	char			**e;
	/* cmd_table */
	char			**av;
}	t_var;

void					init_global(void);

/* Lexical analyzer */
t_ptr					lexer(char *user_input);
t_bool					string_tokens(char **user_input, t_ptr *tokens_head,
							int type, int *order);
t_bool					char_tokens(char **user_input, t_ptr *tokens_head,
							int type, int order);

/* Lexer utils */
t_bool					token_create(char **user_input, t_ptr *tokens_head,
							int type, int order);
int						get_token_length(char *user_input, int type,
							t_ptr tokens_head);
char					*get_token(char *user_input, int token_len);
int						get_type(char user_input);
void					move_user_input(char **user_input);

/* utilities */
t_ptr					find_last_node(t_ptr head);
t_bool					ft_isspace(char c);
char					*ft_realloc(char *to_free, int new_len);
void					dup_and_close(int *end, int i);
void					points_checker(t_var data, char **av);

/* expander */
void					tokens_expander(t_ptr tokens_list, char **envp);
char					*extract_dollar_token(char *ptr_token, char *dollar_tk,
							int dollar_tk_len);
char					*get_value(char *dollar_tk, int *dtk_len, char **envp);
char					*expanding(char *dollar_tk, char *token,
							int tmp_tk_len);
void					move_data(t_expand *data, char *dollar_tk, char *token);

/* expander utils */
char					*find_dollar(char *ptr_token);
void					check_expander_chars(t_expand *d);
int						get_variable_len(char *envp);
char					*retrieve_value(char *envp, char *dollar_tk);
t_bool					check_type(int token_type);

/* expander utils2 */
void					tokens_expander_helper(t_ptr tokens_list,
							char **envp, t_expand d);
int						dollars_count(char *token);
int						get_biggest_len(char *envp, char *dollar_tk);
void					data_move_helper(t_expand *data, char **token);

/* expander utils3 */
t_bool					string_handler(t_ptr *tokens_list);
t_bool					doublequote_handler(t_ptr *tokens_list);
t_bool					singlequote_handler(t_ptr *tokens_list);

/* Parser */
int						parser_tokens(t_ptr tokens_list, t_env *env);
int						pipe_checker(t_ptr tokens_list);
int						redirections_checker(t_ptr tokens_list);
int						semicolon_checker(t_ptr tokens_list);
int						backslash_checker(t_ptr tokens_list);
void					built_in(t_ptr tokens_list);
int						parentheses_checker(t_ptr tokens_list);
int						parser_tokens_2(t_ptr tokens_list);
int						heredoc_next_checker(t_ptr tokens_list);
int						heredoc_append_checker(t_ptr tokens_list);
void					space_skip(t_ptr tokens_list);
void					space_skip_rev(t_ptr tokens_list);
char					*get_unique_filename(int i);
void					new_token_lst(t_ptr tokens_list, int order,
							char *test);
void					filename_write(t_ptr tokens_list, char *filename,
							int order);
int						heredoc(t_ptr tmp, t_ptr tokens_list,
							t_env *envp);
char					*ft_expand_heredoc(char *line, t_env *envp);
char					*ft_delimiter(t_ptr tokens_list, int order);
char					**ft_advanced_split(const char *str);
t_env					*init_env(char **env);
int						count_segments(const char *str, int count);
int						is_valid_char(char c);
char					*allocate_segment(const char *start, int length);
t_ptr					find_last_node2(t_ptr list);
void					ft_free_array(char **array);
void					ft_enter(t_ptr tokens_list, int i);
int						ft_no_expand(t_ptr tmp);
void					test_norm(int fd, char **line);
void					eof_printer(char *delimiter);
void					ft_eraser(t_ptr tmp, char *filename);
void					error(const char *cmd, const char *msg);
char					*ft_strstr(const char *haystack, const char *needle);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strcpy(char *dest, const char *src);
/* new one */
void					free_global_tmp(t_env *tmp);
void					update_exported_variable(char *variable);
t_bool					ft_export_check(char **av, int i);
void					print_env(t_env *env);
t_env					*ft_copy_env(t_env *env);
char					*ft_key(char *variable);
t_bool					is_valid_identifier(char c, int i);
void					update_value(t_env *tmp, char *variable);

/* built_in   	*/
t_bool					exec_builtin(char **av);
t_bool					ft_cd(char **av);
int						nb_args(char **args);
t_bool					ft_export(char **av);
t_bool					is_exported(char *variable);
t_bool					ft_unset(char **av);
t_bool					ft_exit(char **av, t_var data);
t_bool					ft_echo(char **av);
t_bool					ft_env(char **av);

/* signal handler */
void					handler(int signum);
void					signal_handler(void);
void					signal_handler_heredoc(void);
void					ft_handler(int signum);

/* free_and_errors */
void					free_tokens(t_ptr tokens_list);
void					free_all(t_ptr tokens_list, char *user_input,
							char **av);
void					free_cmd_table(char **full_cmd);
void					quotes_error(int quotes_type);
void					print_error(char *error);
void					exit_error(char *error, t_var *data, char **av,
							int exit_code);
void					free_global_env(void);
void					free_child_process(t_var *data, char **av);
void					free_close_child(t_var *data, char **av);

/* utils2 */
void					tokens_order(t_ptr tokens_list);
t_ptr					get_next_pipe(t_ptr tokens_list);
void					get_next_type(t_ptr *tokens_list, t_var d);
t_bool					special_chars_checker(int type);
t_bool					quotes_cmd_checker(t_var d);

/* syntax_builder */
void					syntax_algo(t_ptr tokens_list);
void					check_no_cmd(t_ptr tokens_list);

/* syntax builder utils */
int						check_pipes_num(t_ptr tokens_list);
void					same_type_finder(t_ptr *tokens_list);
t_bool					type_checker(int type);
t_bool					cmd_checker(t_ptr tokens_list);
void					quotes_handler_helper(t_ptr tokens_list, t_var d);

/* syntax builder utils 2 */
t_bool					handle_qt(t_ptr *tokens_list, t_var d);
void					words_finder(t_ptr *tokens_list, t_var d);
t_bool					tmp_checker(t_ptr *tokens_list, t_ptr tmp,
							t_bool *status);
t_bool					multiple_quotes_check(t_var d, t_ptr tmp);
t_bool					types_checker(t_var d, int index, t_ptr tmp);

/* tokens checker (printed on terminal) */
void					check_tokens(t_ptr print_tk);

/* executor */
void					executor(t_ptr tokens_list, char **env,
							char *user_input);

/* tk_optimizer */
void					tokens_list_optimizer(t_ptr *tokens_list);
void					special_chars_refactor(t_ptr tokens_list);
void					node_remover(t_ptr *node);
t_bool					special_chars_finder(t_ptr *tokens_list,
							t_ptr node_add, int type);

/* exucutor uitls */
t_bool					extract_cmd_helper(t_ptr *tokens_list,
							int *i,
							char **full_cmd);
t_bool					get_infos_helper(t_ptr *tokens_list,
							t_bool *flag,
							int *rows);

/* pipes uitls */
void					child_exec_cmd(char **av, t_var *data,
							t_bool pipe_switcher);
void					dup_and_close(int *end, int i);
char					*ft_cmd_path(char *cmd_path);
char					*ft_get_path(char **envp);
char					*ft_find_cmd(char *cmd, char **envp);

/* IO_stream */
t_bool					input_red_stream(t_var *data);
t_bool					input_red_fd(t_ptr *temp, t_var *data);
t_bool					output_red_stream(t_var *data);
t_bool					output_red_fd(t_ptr *temp, t_var *data);
t_bool					output_red_helper(t_ptr *temp, t_var *data,
							t_bool *filename);

/* status_utils */
void					dollar_status_check(t_ptr tokens_list);
char					*expand_status(char *tk, int *i);
int						get_length(char *tk);
void					before_tk_status(char *before, char *tk);
void					after_tk_status(char *after, char *tk);

/* utils 3*/
t_bool					check_single_quotes(t_ptr node);
t_bool					builtin_checker(char *built_in);
void					open_output_fd(t_ptr *temp, t_var *data);
t_bool					check_quotes(t_var *d, t_ptr *tokens_list);
t_bool					space_trim(t_ptr tokens_list);

/* utils 4 */
void					quotes_substitut(char **cmd_table);
void					close_fds(t_var *data);
t_bool					builtin_check(char **av, t_var data,
							t_bool pipe_switcher);
char					**transform_env(void);
void					join_key_value(char *str, char **envp, int i,
							t_env *tmp);

/* utils 5 */
int						big_len(char *str1, char *str2);
t_bool					export_check(char **av, t_var data,
							t_bool pipe_switcher);
t_bool					unset_check(char **av, t_var data,
							t_bool pipe_switcher);
t_bool					exit_check(char **av, t_var data, t_bool pipe_switcher);
t_bool					cd_check(char **av, t_var data, t_bool pipe_switcher);

/* utils 6 */
void					split_words(t_ptr *tk_list);
void					add_nodes(t_ptr tk, char *word);
void					add_node(t_ptr tk, char *word, int type);
void					io_dup_close(t_var *data);
void					status_handle(void);

/* utils 7 */
void					pipe_order_check(t_ptr *tokens_list);
void					pipe_node_remover(t_ptr *last);
void					child_exec_helper(t_var *data, char **av);
void					spliter(char **word, t_ptr tk, int *i);
void					set_tk_exp_len(t_ptr *tokens_list);

/* utils 8 */
void					change_pwd(t_env *envs, const char *old_pwd,
							const char *pwd);
void					ft_sort_env(t_env *env);
void					set_env(t_env *env, const char *key, const char *value);

/* utils 9 */
void					handler_2(int signum);
void					hendler_1(int signum);
void					ft_strncpy(char *dst, char const *s, int bytes);
void					ft_underscore(char *av);

#endif /* MINIHELL_H */
