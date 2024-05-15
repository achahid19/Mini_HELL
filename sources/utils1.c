/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:36:20 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/14 08:36:22 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

token_ptr	find_last_node(token_ptr head);
t_bool		ft_isspace(char c);
void		lexer_helper(char **user_input, token_ptr *tokens_head,
				int type, int *order);

/**
 * find_last_node - iterates over a linked list
 * to find the last node.
 * @head: pointer to the first node
 * 
 * Return: pointer to the last node.
*/
token_ptr	find_last_node(token_ptr head)
{
	while (head != NULL)
	{
		if (head->next == NULL)
			break ;
		head = head->next;
	}
	return (head);
}

/**
 * ft_isspace - checks if the character c
 * is a space or not.
 * @c: character
 * 
 * Return: boolean.
*/
t_bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/**
 * lexer_helper - handler of complicated cases
 * such as: string_token for doublequote_token
 * and singlequote_token
 * @user_input: double pointer to the input
 * @tokens_head: double pointer to the list of tokens
 * @type: token's type
 * @order: order of token on the input
 * 
 * Return: void.
*/
void	lexer_helper(char **user_input, token_ptr *tokens_head,
			int type, int *order)
{
	char	c;

	token_create(user_input, tokens_head, type, *order);
	*order += 1;
	c = user_input[0][1];
	if (c != '"' && c != '\'' && c)
	{
		*user_input += 1;
		token_create(user_input, tokens_head, string_token, *order);
		*order += 1;
	}
	c = user_input[0][1];
	if (c == '"' || c == '\'')
	{
		*user_input += 1; // move the user_input pointer
		if (c == '"')
			token_create(user_input, tokens_head, doublequote_token, *order);
		else if (c == '\'')
			token_create(user_input, tokens_head, singlequote_token, *order);
		*order += 1;
	}
}
