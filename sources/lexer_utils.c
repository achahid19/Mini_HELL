/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:28:12 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/16 09:28:14 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

void    token_create(char **user_input, token_ptr *tokens_head,
	    				int type, int order);
int	    get_token_length(char *user_input, int type);
char    *get_token(char *user_input, int token_len);
int	    get_type(char user_input);

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
	new->previous = last;
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
int	get_token_length(char *user_input, int type)
{
	int	len;

	len = 0;
	if (type == word_token)
	{
		while (get_type(user_input[len]) == word_token && user_input[len])
			len++;
	}
	else if (type == string_token)
	{
		while (user_input[len] != '"' && user_input[len] != '\''
			&& user_input[len])
			len++;
	}
	else if (type == heredoc_token || type == append_token)
		len = 2;
	else
		len = 1;
	return (len);
}

/**
 * get_token - allocates n bytes based on token_len
 * to store the token
 * @user_input: pointer to the input
 * @token_len: token's length
 * 
 * Return: pointer to the new token.
*/
char	*get_token(char *user_input, int token_len)
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

/**
 * get_type - get the type of each element
 * on user_input
 * @user_input: character to check
 * 
 * Return: token's type
*/
int	get_type(char user_input)
{
	if (ft_isspace(user_input) == true)
		return (whitespace_token);
	else if (user_input == '|')
		return (pipe_token);
	else if (user_input == '(')
		return (lbracket_token);
	else if (user_input == ')')
		return (rbracket_token);
	else if (user_input == '<')
		return (leftred_token);
	else if (user_input == '>')
		return (rightred_token);
	else if (user_input == '"')
		return (doublequote_token);
	else if (user_input == '\'')
		return (singlequote_token);
	else
		return (word_token);
}
