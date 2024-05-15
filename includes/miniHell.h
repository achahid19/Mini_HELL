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
    right_parenthesis_token = 6,
    left_parenthesis_token = 7,
    option_token = 8,
    leftred_token = 9,
    rightred_token = 10
}   t_type;

/**
 * I know u for compiler
*/
typedef struct  s_token t_token;
typedef t_token *token_ptr;

// lexer: token's data
typedef struct s_token
{
    char        *token;
    int         order; // index of the token on the input
    t_type      token_type; // define a type of each encoutred token
    int         token_length;
    token_ptr   next;
}   t_token;

typedef t_token *token_ptr;

/* Lexical analyzer */
token_ptr   lexer(char *user_input);
void	    lexer_helper(char **user_input, token_ptr *tokens_head,
                int type, int *order);
void		token_create(char **user_input, token_ptr *tokens_head,
				int type, int order);

/* utilities */
token_ptr	find_last_node(token_ptr head);
t_bool      ft_isspace(char c);

#endif /* MINIHELL_H */
