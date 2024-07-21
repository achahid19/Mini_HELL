/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:20:09 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/21 14:20:10 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	pipe_order_check(token_ptr *tokens_list);
void	pipe_node_remover(token_ptr *last);

/**
 * pipe_order_check -
 */
void	pipe_order_check(token_ptr *tokens_list)
{
	token_ptr	last;
	token_ptr	begin;

	if (*tokens_list == NULL)
		return ;
	last = find_last_node((*tokens_list));
	while (last->token_type == pipe_token)
	{
		if (last->previous == NULL)
			*tokens_list = NULL;
		pipe_node_remover(&last);
		if (last == NULL)
			break ;
	}
}

/**
 * pipe_node_remover -
 */
void	pipe_node_remover(token_ptr *last)
{
	token_ptr	to_free;

	to_free = (*last);
	free((*last)->token);
	(*last) = (*last)->previous;
	if ((*last))
		(*last)->next = NULL;
	free(to_free);
}

/**
 * space_last_skip -
 */
/* void	space_last_skip(token_ptr *last)
{
	while ((*last)->token_type == whitespace_token)
	{
		(*last) = (*last)->previous;
		if ((*last) == NULL)
			return ;
	}
} */
