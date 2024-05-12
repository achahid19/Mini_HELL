/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:17 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/05 10:30:19 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

token_ptr   lexer(char *user_input)
{
    // identify methacharacters; characters that separates
    // words or arguments
    size_t  index;

    index = 0;
    while (*user_input != '\0')
    {
        if (is_space(*user_input) == true)
        {
            while (is_space(*user_input) == true)
            {
                token_create(*user_input, whitespace_token);
                user_input++;
                if (*user_input == '\0')
                    break ;
            }
        }
        else if(*user_input == '|')
            token_create(*user_input, pipe_token);
        else if (*user_input == '\'')
            token_create(*user_input, singlequote_token);
        else if (*user_input == '"')
            token_create(*user_input, doublequote_token);
        else if (*user_input == '(')
            token_create(*user_input, left_parenthesis_token);
        else if (*user_input == ')')
            token_create(*user_input, right_parenthesis_token);
        else if (*user_input == '-')
            token_create(*user_input, option_token);

    }
}
