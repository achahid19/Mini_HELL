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
# include "../get_next_line/get_next_line.h" // read user's line
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
    singlequote_token = 5,
    doublequote_token = 6,
    right_parenthesis_token = 7,
    left_parenthesis_token = 8,
    option_token = 9
}   t_type;

// lexer: token's data
typedef struct s_token
{
    char    *token;
    int     order; // index of the token on the input
    t_type  token_type; // define a type of each encoutred token
}   t_token;

typedef t_token *token_ptr;

#endif /* MINIHELL_H */
