/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:56:28 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/10 16:56:29 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	string_handler(t_ptr *tokens_list);
t_bool	doublequote_handler(t_ptr *tokens_list);
t_bool	singlequote_handler(t_ptr *tokens_list);

/**
 * string_hanlder - handle the execution of the
 * expansion of dollar sign, in double quoted string
*/
t_bool	string_handler(t_ptr *tokens_list)
{
	if ((*tokens_list)->token_type == doublequote_token)
	{
		if (doublequote_handler(tokens_list) == false)
			return (false);
	}
	else if ((*tokens_list)->token_type == singlequote_token)
	{
		if (singlequote_handler(tokens_list) == false)
			return (false);
	}
	return (true);
}

/**
 * doublquote_handler -
*/
t_bool	doublequote_handler(t_ptr *tokens_list)
{
	*tokens_list = (*tokens_list)->next;
	if (*tokens_list == NULL)
		return (false);
	if ((*tokens_list)->token_type == doublequote_token)
	{
		*(tokens_list) = (*tokens_list)->next;
		return (false);
	}
	return (true);
}

/**
 * singlequote_handler -
*/
t_bool	singlequote_handler(t_ptr *tokens_list)
{
	*tokens_list = (*tokens_list)->next;
	if (*tokens_list == NULL)
		return (false);
	if ((*tokens_list)->token_type == singlequote_token)
	{
		*(tokens_list) = (*tokens_list)->next;
		return (false);
	}
	if ((*tokens_list)->token_type == string_token)
	{
		*(tokens_list) = (*tokens_list)->next->next;
		return (false);
	}
	return (true);
}
