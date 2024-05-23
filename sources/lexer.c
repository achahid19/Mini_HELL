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

token_ptr	lexer(char *user_input);
t_bool		string_tokens(char **user_input, token_ptr *tokens_head,
							int type, int *order);
void		char_tokens(char **user_input, token_ptr *tokens_head,
							int type, int order);

/**
 * lexer - Lexical Analyser; tokenize the
 * readed input into simpliest tokens
 * @user_input: full command taken from the prompt or from an fd
 * 
 * Return: a list of tokens.
*/
token_ptr	lexer(char *user_input)
{
	token_ptr	tokens_head;
	int			order;
	int			type;

	tokens_head = NULL;
	order = 1;
	while (*user_input)
	{
		/* printf("------> pointing at: %s\n", user_input); */
		type = get_type(*user_input);
		if (type == leftred_token && type == get_type(*(user_input + 1)))
			token_create(&user_input, &tokens_head, heredoc_token, order++);
		else if (type == rightred_token && type == get_type(*(user_input + 1)))
			token_create(&user_input, &tokens_head, append_token, order++);
		else if (type == singlequote_token || type == doublequote_token)
		{
			if (string_tokens(&user_input, &tokens_head, type, &order) == false)
				return (NULL);
		}
		else
			char_tokens(&user_input, &tokens_head, type, order++);
		if (*user_input)
			user_input++;
	}
	return (tokens_head);
}

/**
 * string_tokens - handler of complicated cases
 * such as: string_token for doublequote_token
 * and singlequote_token
 * @user_input: double pointer to the input
 * @tokens_head: double pointer to the list of tokens
 * @type: token's type
 * @order: order of token on the input
 * 
 * Return: void.
*/
t_bool	string_tokens(char **user_input, token_ptr *tokens_head,
			int type, int *order)
{
	token_create(user_input, tokens_head, type, *order);
	*order += 1;
	*user_input += 1;
	if (get_token_length(*user_input, string_token, *tokens_head) != 0)
	{
		if (token_create(user_input, tokens_head, string_token, *order) == false)
			return (false);
		*order += 1;
		*user_input += 1;
	}
	else
	{
		if (get_type(**user_input) != type)
			return (false);
	}
	token_create(user_input, tokens_head, type, *order);
	*order += 1;
	return (true);
}

/**
 * char_token - create the token based on his type
 * @user_input: double pointer to user_input
 * @tokens_head: pointer to the list of tokens
 * @type: token's type
 * @order: order of the token on user_input
 * 
 * Return: void.
*/
void	char_tokens(char **user_input, token_ptr *tokens_head,
						int type, int order)
{
	if (type == whitespace_token)
		token_create(user_input, tokens_head, whitespace_token, order);
	else if(type == pipe_token)
		token_create(user_input, tokens_head, pipe_token, order);
	else if (type == lbracket_token)
		token_create(user_input, tokens_head, lbracket_token, order);
	else if (type == rbracket_token)
		token_create(user_input, tokens_head, rbracket_token, order);
	else if (type == leftred_token)
		token_create(user_input, tokens_head, leftred_token, order);
	else if (type == rightred_token)
		token_create(user_input, tokens_head, rightred_token, order);
	else
		token_create(user_input, tokens_head, word_token, order);
}
