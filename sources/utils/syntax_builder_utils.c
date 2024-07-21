/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_builder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:49:16 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/26 09:49:17 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int		check_pipes_num(token_ptr tokens_list);
void	same_type_finder(token_ptr *tokens_list);
t_bool	type_checker(int type);
t_bool	cmd_checker(token_ptr tokens_list);
void	quotes_handler_helper(token_ptr tokens_list, t_var d);

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
 * same_type_finder -
*/
void	same_type_finder(token_ptr *tokens_list)
{
	while ((*tokens_list)->token_type != word_token
		&& (*tokens_list)->token_type != string_token
		&& (*tokens_list)->token_type != filename_token)
	{
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) == NULL)
			break ;
	}
}

/**
 * type_checker -
*/
t_bool	type_checker(int type)
{
	return (type == heredoc_token || type == leftred_token
		|| type == rightred_token || type == append_token);
}

/**
 * cmd_checker -
*/
t_bool	cmd_checker(token_ptr tokens_list)
{
	while (tokens_list)
	{
		if (tokens_list->token_type == cmd)
			return (true);
		tokens_list = tokens_list->next;
	}
	return (false);
}

/**
 * quotes_handler_helper -
*/
void	quotes_handler_helper(token_ptr tokens_list, t_var d)
{
	t_bool	status;

	while (tokens_list)
	{
		d.type_next = 12;
		d.type_next_next = 12;
		d.type_previous = 12;
		d.is_space = false;
		if (tokens_list->token_type == pipe_token)
			return ;
		d.type = tokens_list->token_type;
		if (d.type == doublequote_token || d.type == singlequote_token)
		{
			status = handle_qt(&tokens_list, d);
			if (status == false)
				return ;
			else if (status == true)
				continue ;
		}
		tokens_list = tokens_list->next;
		if (tokens_list == NULL)
			return ;
		if (tokens_list->token_type == pipe_token)
			return ;
	}
}
