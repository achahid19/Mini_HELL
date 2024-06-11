/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_optimizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 04:29:05 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/11 04:29:06 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void		tokens_list_optimizer(token_ptr *tokens_list);
static void	whitespace_remover(token_ptr *tokens_list,
				token_ptr free_node, token_ptr previous);

/**
 * tokens_list_optimizer -
*/
void	tokens_list_optimizer(token_ptr *tokens_list)
{
	token_ptr	tmp;
	token_ptr	free_node;
	token_ptr	previous;

	tmp = *tokens_list;
	free_node = NULL;
	previous = NULL;
	whitespace_remover(tokens_list, free_node, previous);
	tokens_order(*tokens_list);
	// if (*tokens_list != NULL)
	// 	check_tokens(*tokens_list);
}

/**
 * whitespace_remover -
*/
static void	whitespace_remover(token_ptr *tokens_list,
				token_ptr free_node, token_ptr previous)
{
	token_ptr	tmp;

	tmp = *tokens_list;
	while (tmp)
	{
		if (tmp->token_length == 0)
		{
			free_node = tmp;
			previous = tmp->previous;
			tmp = tmp->next;
			if (previous != NULL)
				previous->next = tmp;
			else
				*tokens_list = tmp;
			if (tmp != NULL)
				tmp->previous = previous;
			if (previous == NULL && tmp == NULL)
				*tokens_list = NULL;
			free(free_node->token);
			free(free_node);
			free_node = NULL;
			continue ;
		}
		tmp = tmp->next;
	}
}
