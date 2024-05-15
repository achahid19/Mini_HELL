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
void		token_create(char **user_input, token_ptr *tokens_head,
				int type, int order);
static int	get_token_length(char *user_input, int type);
static char	*get_token(char *user_input, int token_len);

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

	tokens_head = NULL;
	order = 1;
	while (*user_input)
	{
		printf("pointing in: %s\n", user_input);
		if (ft_isspace(*user_input) == true)
			token_create(&user_input, &tokens_head, whitespace_token, order++);
		else if(*user_input == '|')
			token_create(&user_input, &tokens_head, pipe_token, order++);
		else if (*user_input == '\'')
			lexer_helper(&user_input, &tokens_head, singlequote_token, &order);
		else if (*user_input == '"')
			lexer_helper(&user_input, &tokens_head, doublequote_token, &order);
		else if (*user_input == '(')
			token_create(&user_input, &tokens_head, left_parenthesis_token, order++);
		else if (*user_input == ')')
			token_create(&user_input, &tokens_head, right_parenthesis_token, order++);
		else if (*user_input == '-')
			token_create(&user_input, &tokens_head, option_token, order++);
		else if (ft_isalpha(*user_input) == true)
			token_create(&user_input, &tokens_head, word_token, order++);
		if (*user_input)
			user_input++;
		
	}
	return (tokens_head);
}

/**
 * token_create - create the specified token based on the type.
 * @user_input: double pointer to the input
 * @tokes_head: double pointer to the tokens list
 * @type: define the type of the token
 * @order: order of the token on the input
 * 
 * Return: void.
*/
void	token_create(char **user_input, token_ptr *tokens_head, int type, int order)
{
	token_ptr	new;
	token_ptr	last;

	last = find_last_node(*tokens_head);
	new = malloc(sizeof(t_token)); // TODO if fail.
	new->token_length = get_token_length(*user_input, type);
	new->token = get_token(*user_input, new->token_length);
	new->order = order++;
	new->token_type = type;
	new->next = NULL;
	if (last != NULL)
		last->next = new;
	if (*tokens_head == NULL)
		*tokens_head = new;
	*user_input += new->token_length - 1; // move user_input pointer.
}

/**
 * get_token_length - get token's length
 * @input: pointer to the input
 * @type: type of the token (defined t_type)
 * 
 * Return: token's length
*/
static int	get_token_length(char *user_input, int type)
{
	int	length;

	length = 0;
	if (type == word_token)
	{
		while (ft_isspace(*user_input) == false && *user_input
				&& *user_input != '"' && *user_input != '\'')
		{
			user_input++;
			length++;
		}
	}
	else if (type == string_token)
	{
		while (*user_input != '"' && *user_input != '\'' && *user_input)
		{
			user_input++;
			length++;
		}
	}
	else
		length = 1;
	return (length);
}

/**
 * get_token - allocates n bytes based on token_len
 * to store the token
 * @user_input: pointer to the input
 * @token_len: token's length
 * 
 * Return: pointer to the new token.
*/
static char	*get_token(char *user_input, int token_len)
{
	char	*token;
	size_t	index;

	token = malloc(sizeof(char) * token_len + 1); // TO FREE WHEN DONE WITH IT + TO DO PROTECT
	index = 0;
	while (token_len--)
	{
		token[index] = user_input[index];
		index++;
	}
	token[index] = '\0';
	return (token);
}
