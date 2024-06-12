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
int			check_pipes_num(token_ptr tokens_list);
static void	special_chars(token_ptr tokens_list, int type);
static void	assign_cmd(token_ptr tokens_list);
void	check_no_cmd(token_ptr tokens_list);
static void	quotes_handler(token_ptr tokens_list);

/**
 * syntax_algo -
*/
void	syntax_algo(token_ptr tokens_list)
{
	int			type;
	int			pipes;

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
 * check_pipes_num -
*/
int	check_pipes_num(token_ptr tokens_list)
{
	int	pipes;

	pipes = 1;
	while (tokens_list)
	{
		if (tokens_list->token_type == pipe_token)
			pipes++;
		tokens_list = tokens_list->next;
	}
	return (pipes);
}

/**
 * special_chars -
*/
static void	special_chars(token_ptr tokens_list, int type)
{
	while (tokens_list)
		{
			if (type_checker(tokens_list->token_type) == true)
			{
				type = tokens_list->token_type;
				tokens_list = tokens_list->next;
				if (tokens_list != NULL)
				{
					while (tokens_list->token_type != word_token
							&& tokens_list->token_type != string_token)
					{
						tokens_list = tokens_list->next;
						if (tokens_list == NULL)
							break ;
					}
					if (tokens_list != NULL)
						tokens_list->token_type = type;
					else
						break ;
				}
				else
					break ;
			}
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
				return ;
			if (tokens_list->token_type == pipe_token)
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
	}
}

/**
 * check_no_cmd -
*/
 void	check_no_cmd(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == cmd)
			return ;
		tmp = tmp->next;
	}
	while(tokens_list)
	{
		while (tokens_list->token_type == whitespace_token)
		{
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
				return ;
		}
		if (tokens_list->token_type == doublequote_token ||
			tokens_list->token_type == singlequote_token)
		{
			tokens_list->token_type = cmd;
			tokens_list->next->token_type = cmd;
		}
		tokens_list = get_next_pipe(tokens_list);
		if (tokens_list != NULL)
			tokens_list = tokens_list->next;
	}
}

static void	quotes_handler(token_ptr tokens_list)
{
	int	type_next;
	int	type_previous;
	int	type;

	type_next = 12;
	type_previous = 12;
	if (tokens_list == NULL)
		return ;
	if (tokens_list->token_type == pipe_token)
		tokens_list = tokens_list->next;
	while (tokens_list)
	{
		if (tokens_list->token_type == pipe_token)
			return ;
		type = tokens_list->token_type;
		if (type == doublequote_token || type == singlequote_token)
		{	
			if (tokens_list->next != NULL)
				type_next = tokens_list->next->token_type;
			if (tokens_list->previous != NULL)
				type_previous = tokens_list->previous->token_type;
			if (type_next == type && type_previous == whitespace_token)
			{
				tokens_list->token_type = word_token;
				tokens_list->next->token_type = word_token;
			}
		}
		tokens_list = tokens_list->next;
	}
}
