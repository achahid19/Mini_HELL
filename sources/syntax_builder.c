/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:47:22 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/10 15:47:24 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

void		syntax_algo(token_ptr tokens_list);
static void	special_chars(token_ptr tokens_list, int type);
static void	assign_cmd(token_ptr tokens_list);
void		check_no_cmd(token_ptr tokens_list);
static void	quotes_handler(token_ptr tokens_list);

/**
 * syntax_algo -
*/
void	syntax_algo(token_ptr tokens_list)
{
	int		type;
	int		pipes;

	pipes = check_pipes_num(tokens_list);
	while (pipes--)
	{
		special_chars(tokens_list, type);
		assign_cmd(tokens_list);
		check_no_cmd(tokens_list);
		quotes_handler(tokens_list);
		special_chars_refactor(tokens_list);
		tokens_list = get_next_pipe(tokens_list);
		if (tokens_list == NULL)
			break ;
		tokens_list = tokens_list->next;
	}
}

/**
 * special_chars - spot special chras (>>, <<, <, >)
 * and look for their extensions (tokens of the same type).
*/
static void	special_chars(token_ptr tokens_list, int type)
{
	while (tokens_list)
	{
		if (type_checker(tokens_list->token_type) == true)
		{
			type = tokens_list->token_type;
			tokens_list = tokens_list->next;
			same_type_finder(&tokens_list);
			if (tokens_list != NULL)
				tokens_list->token_type = type;
			else
				break ;
		}
		tokens_list = tokens_list->next;
		if (tokens_list == NULL)
			return ;
		else if (tokens_list->token_type == pipe_token)
			return ;
	}
}

/**
 * assign_cmd -
*/
static void	assign_cmd(token_ptr tokens_list)
{
	while (tokens_list)
	{
		if (tokens_list->token_type == word_token ||
			tokens_list->token_type == string_token)
		{
			tokens_list->token_type = cmd;
			break ;
		}
		tokens_list = tokens_list->next;
		if (tokens_list == NULL)
			return ;
		else if (tokens_list->token_type == pipe_token)
			return ;
	}
}

/**
 * check_special_chars -
*/
t_bool	check_special_chars(token_ptr tokens_list)
{
	int	type;

	printf("entred\n");
	if (tokens_list->next->next != NULL)
	{
		type = tokens_list->next->next->token_type;
		printf("type is: %d\n", type);
		while (type == doublequote_token || type == singlequote_token)
		{
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
				return (false);
			type = tokens_list->token_type;
			
		}
		if (type == append_token || type == heredoc_token
			|| type == leftred_token || type == rightred_token)
			return (false);
	}
	return (true);
}

/**
 * quotes_finder -
*/
t_bool	quotes_finder(int type)
{
	return (type == doublequote_token
			|| type == singlequote_token);
}

/**
 * check_no_cmd -
*/
 void	check_no_cmd(token_ptr tokens_list)
{
	if (cmd_checker(tokens_list) == true)
		return ;
	while(tokens_list)
	{
		while (tokens_list->token_type == whitespace_token)
		{
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
					return ;
		}
		if (quotes_finder(tokens_list->token_type) == true)
		{
			if (quotes_finder(tokens_list->next->token_type) == true)
			{
				tokens_list->token_type = cmd;
				tokens_list->next->token_type = cmd;
			}
		}
		tokens_list = get_next_pipe(tokens_list);
		if (tokens_list != NULL)
			tokens_list = tokens_list->next;
	}
}

/**
 * quotes_hanlder -
*/
static void	quotes_handler(token_ptr tokens_list)
{
	t_var	d;
	
	if (tokens_list == NULL)
		return ;
	if (tokens_list->token_type == pipe_token)
		tokens_list = tokens_list->next;
	quotes_handler_helper(tokens_list, d);
}
