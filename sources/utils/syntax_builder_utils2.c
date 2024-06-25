#include "../../includes/miniHell.h"

t_bool	handle_qt(token_ptr	*tokens_list, t_var d);
void	get_next_type(token_ptr *tokens_list, t_var d);
void	words_finder(token_ptr *tokens_list, t_var d);
t_bool	tmp_checker(token_ptr *tokens_list, token_ptr tmp, t_bool *status);

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
	// while (d.tmp->token_type == whitespace_token)
	// {
	// 	d.is_space = true;
	// 	d.tmp = d.tmp->previous;
	// 	if (d.tmp != NULL)
	// 		d.type_previous = d.tmp->token_type;
	// 	else
	// 		break ;
	// }
	// if (tmp_checker(tokens_list, d.tmp, &status) == false)
	// 	return (status);
	return (words_finder(tokens_list, d), success);
}

/**
 * get_next_type -
*/
void	get_next_type(token_ptr *tokens_list, t_var d)
{
	if ((*tokens_list)->next != NULL)
	{
		d.type_next = (*tokens_list)->next->token_type;
		if ((*tokens_list)->next->next != NULL)
		d.type_next_next = (*tokens_list)->next->next->token_type;
	}
}

/**
 * words_finder -
*/
void	words_finder(token_ptr *tokens_list, t_var d)
{
	if ((*tokens_list)->next == NULL)
		return ;
	if (cmd_checker(*tokens_list) == true)
		return ;
	d.type_next = (*tokens_list)->next->token_type;
	if ((*tokens_list)->next->next != NULL)
	{
		if ((*tokens_list)->next->next->token_type == whitespace_token
			|| (*tokens_list)->next->next->token_type == doublequote_token
			|| (*tokens_list)->next->next->token_type == singlequote_token)
			d.type_next_next = (*tokens_list)->next->next->token_type;
	}
	else if ((*tokens_list)->next->next == NULL)
		d.type_next_next = 13;
	if ((*tokens_list)->previous != NULL)
	{
		if ((*tokens_list)->previous->token_type == whitespace_token)
			d.type_previous = (*tokens_list)->previous->token_type;
	}
	if ((d.type_next == doublequote_token || d.type_next == singlequote_token)
		&& (d.type_previous == whitespace_token) && (d.type_next_next == whitespace_token
		|| d.type_next_next == doublequote_token
		|| d.type_next_next == singlequote_token || d.type_next_next == 13))
	{
		(*tokens_list)->token_type = word_token;
	 	(*tokens_list)->next->token_type = word_token;
	}
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
