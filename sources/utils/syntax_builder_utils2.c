/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_builder_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:51:45 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/26 09:51:46 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	handle_qt(token_ptr	*tokens_list, t_var d);
t_bool	tmp_checker(token_ptr *tokens_list, token_ptr tmp, t_bool *status);
void	words_finder(token_ptr *tokens_list, t_var d);
t_bool	types_checker(t_var d, int index, token_ptr tmp);
t_bool	multiple_quotes_check(t_var d, token_ptr tmp);

/**
 * handle_qt -
*/
t_bool	handle_qt(token_ptr	*tokens_list, t_var d)
{
	t_bool	status;
	t_bool	success;

	success = 2;
	get_next_type(tokens_list, d);
	d.tmp = (*tokens_list)->previous;
	if (tmp_checker(tokens_list, d.tmp, &status) == false)
		return (status);
	words_finder(tokens_list, d);
	return (success);
}

/**
 * tmp_checker -
*/
t_bool	tmp_checker(token_ptr *tokens_list, token_ptr tmp, t_bool *status)
{
	t_bool	skip;

	skip = 2;
	if (tmp == NULL)
	{
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list)->token_type == pipe_token)
		{
			*status = false;
			return (false);
		}
		*status = true;
		return (false);
	}
	return (skip);
}

/**
 * words_finder -
*/
void	words_finder(token_ptr *tk_list, t_var d)
{
	if ((*tk_list)->next == NULL || cmd_checker(*tk_list) == true)
		return ;
	d.type_next = (*tk_list)->next->token_type;
	if ((*tk_list)->next->next != NULL)
	{
		if (types_checker(d, 2, (*tk_list)) == true)
			d.type_next_next = (*tk_list)->next->next->token_type;
	}
	else if ((*tk_list)->next->next == NULL)
		d.type_next_next = 13;
	if ((*tk_list)->previous != NULL)
	{
		if ((*tk_list)->previous->token_type == whitespace_token
			|| (*tk_list)->previous->token_type == pipe_token)
			d.type_previous = (*tk_list)->previous->token_type;
	}
	if (types_checker(d, 1, NULL) == true)
	{
		if (multiple_quotes_check(d, (*tk_list)) == false)
			return ;
		(*tk_list)->token_type = word_token;
		(*tk_list)->next->token_type = word_token;
	}
}

/**
 * word_assign_checker -
*/
t_bool	types_checker(t_var d, int index, token_ptr tmp)
{
	if (index == 1)
	{
		return ((d.type_next == doublequote_token
				|| d.type_next == singlequote_token)
			&& (d.type_previous == whitespace_token || d.type_previous == 13
				|| d.type_previous == pipe_token)
			&& (d.type_next_next == whitespace_token
				|| d.type_next_next == doublequote_token
				|| d.type_next_next == singlequote_token
				|| d.type_next_next == 13
				|| d.type_next_next == leftred_token
				|| d.type_next_next == rightred_token
				|| d.type_next_next == append_token));
	}
	else if (index == 2)
	{
		return (tmp->next->next->token_type == whitespace_token
			|| tmp->next->next->token_type == doublequote_token
			|| tmp->next->next->token_type == singlequote_token
			|| tmp->next->next->token_type == append_token
			|| tmp->next->next->token_type == heredoc_token
			|| tmp->next->next->token_type == leftred_token
			|| tmp->next->next->token_type == rightred_token);
	}
	return (1337);
}

/**
 * multiple_quotes_check -
*/
t_bool	multiple_quotes_check(t_var d, token_ptr tmp)
{
	if (d.type_next_next == doublequote_token
		|| d.type_next_next == singlequote_token)
	{
		while (tmp)
		{
			tmp = tmp->next;
			if (tmp == NULL)
				return (true);
			if (tmp->token_type == whitespace_token
				/* || tmp->token_type == rightred_token
				|| tmp->token_type == leftred_token
				|| tmp->token_type == heredoc_token
				|| tmp->token_type == append_token */)
				return (true);
			if (tmp->token_type != doublequote_token
				&& tmp->token_type != singlequote_token)
				return (false);
		}
	}
	return (true);
}
