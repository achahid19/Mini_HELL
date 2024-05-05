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


#endif /* MINIHELL_H */
