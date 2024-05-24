/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniHell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:31:11 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/05 10:31:12 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H
# include <stdio.h> // for debugging
# include <unistd.h> // write ...
# include <limits.h> // INT_MAX ...
# include <stdlib.h> // malloc, free ...
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/* fd */
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// define a set of named integer constant
typedef enum e_bool
{
	false = 0,
	true = 1
}   t_bool;

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
	append_token = 11
}   t_type;

/**
 * I know u for compiler
*/
typedef struct  s_token t_token;
typedef t_token *token_ptr;

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

typedef t_token *token_ptr;

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
}	t_expand;

/* Lexical analyzer */
token_ptr	lexer(char *user_input);
t_bool		string_tokens(char **user_input, token_ptr *tokens_head,
							int type, int *order);
void		char_tokens(char **user_input, token_ptr *tokens_head,
							int type, int order);

/* Lexer utils */
t_bool		token_create(char **user_input, token_ptr *tokens_head,
							int type, int order);
int			get_token_length(char *user_input, int type, token_ptr tokens_head);
char		*get_token(char *user_input, int token_len);
int			get_type(char user_input);

/* utilities */
token_ptr	find_last_node(token_ptr head);
t_bool		ft_isspace(char c);
char		*ft_realloc(char *to_free, int new_len);

/* expander */
void		tokens_expander(token_ptr tokens_list, char **envp);
t_bool		check_expander_chars(char c);

/* expander utils */
char		*find_dollar(char *ptr_token);
t_bool  	check_expander_chars(char c);
int			get_variable_len(char *envp);
char		*retrieve_value(char *envp, char *dollar_tk);
t_bool		check_type(int token_type);

/* expnader utils2 */
t_bool		string_handler(token_ptr *tokens_list);

#endif /* MINIHELL_H */
