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

void			syntax_algo(token_ptr tokens_list);
static void		special_chars(token_ptr tokens_list, int type);
static void		assign_cmd(token_ptr tokens_list);
static t_bool	quotes_cmd(token_ptr *tokens_list);
static void		quotes_handler(token_ptr tokens_list);

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
		if (quotes_cmd(&tokens_list) == true)
			return ;
		if (tokens_list->token_type == word_token
			|| tokens_list->token_type == string_token)
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
 * quotes_cmd -
*/
static t_bool	quotes_cmd(token_ptr *tokens_list)
{
	t_var	d;

	if ((*tokens_list)->next != NULL)
	{
		if ((*tokens_list)->next->token_type != doublequote_token
			&& (*tokens_list)->next->token_type != singlequote_token)
			return (true);
	}
	if (check_quotes(&d, tokens_list) == false)
		return (false);
	if (quotes_cmd_checker(d) == true)
	{
		(*tokens_list)->token_type = cmd;
		(*tokens_list)->next->token_type = cmd;
		return (true);
	}
	(*tokens_list) = (*tokens_list)->next;
	return (false);
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
