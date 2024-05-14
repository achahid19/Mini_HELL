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

t_bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*get_token(char *str, int token_len)
{
	char	*token;
	size_t	index;

	token = malloc(sizeof(char) * token_len); // TO FREE WHEN DONE WITH IT + TO DO PROTECT
	index = 0;
	while (token_len--)
	{
		token[index] = str[index];
		index++;
	}
	return (token);
}

static int	get_sw_length(char *user_input, int type)
{
	int	length;

	length = 0;
	if (type == word_token)
	{
		while (ft_isspace(*user_input) == false && *user_input)
		{
			user_input++;
			length++;
		}
	}
	else if (type == string_token)
	{
		while (*user_input != '"' && *user_input)
		{
			user_input++;
			length++;
		}
	}
	return (length);
}

static void	token_create(char **user_input, token_ptr *tokens_head, int type, int order)
{
	token_ptr	tmp;
	token_ptr	new;


	tmp = *tokens_head;
	if (type == string_token || type == word_token)
	{
		while (tmp != NULL)
		{
			// stop at the last node.
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
		new = malloc(sizeof(t_token)); // TODO if fail.
		new->token_length = get_sw_length(*user_input, type);
		new->token = get_token(*user_input, new->token_length);
		new->order = order++;
		new->token_type = type;
		new->next = NULL;
		if (tmp != NULL)
			tmp->next = new;
		if (*tokens_head == NULL)
			*tokens_head = new;
		*user_input += new->token_length;
	}
	else
	{
		while (tmp != NULL)
		{
			// stop at the last node.
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
		new = malloc(sizeof(t_token)); // TODO if fail.
		new->token = get_token(*user_input, 1);
		new->order = order++;
		new->token_type = type;
		new->token_length = 1;
		new->next = NULL;
		if (tmp != NULL)
			tmp->next = new;
		if (*tokens_head == NULL)
			*tokens_head = new;
	}
}

token_ptr	lexer(char *user_input)
{
	token_ptr	tokens_head;
	static int 	order;

	tokens_head = NULL;
	order = 1;
	while (*user_input)
	{
		if (ft_isspace(*user_input) == true)
			token_create(&user_input, &tokens_head, whitespace_token, order++);
		else if(*user_input == '|')
			token_create(&user_input, &tokens_head, pipe_token, order++);
		else if (*user_input == '\'')
			token_create(&user_input, &tokens_head, singlequote_token, order++);
		else if (*user_input == '"')
			token_create(&user_input, &tokens_head, doublequote_token, order++);
		else if (*user_input == '(')
			token_create(&user_input, &tokens_head, left_parenthesis_token, order++);
		else if (*user_input == ')')
			token_create(&user_input, &tokens_head, right_parenthesis_token, order++);
		else if (*user_input == '-')
			token_create(&user_input, &tokens_head, option_token, order++);
		else if (*user_input == '"' && ft_isalpha(*(user_input + 1)) == true)
			token_create(&user_input, &tokens_head, string_token, order++);
		else if (ft_isalpha(*user_input) == true)
			token_create(&user_input, &tokens_head, word_token, order++);
		if (*user_input)
			user_input++;
	}
	order = 0;
	return (tokens_head);
}
