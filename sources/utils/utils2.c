/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_list_opti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:33:44 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/06 20:44:27 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void		tokens_order(token_ptr tokens_list);
token_ptr	get_next_pipe(token_ptr tokens_list);
void		get_next_type(token_ptr *tokens_list, t_var d);

/**
 * tokens_order -
*/
void	tokens_order(token_ptr tokens_list)
{
	int	order;

	order = 1;
	while (tokens_list)
	{
		tokens_list->order = order;
		order++;
		tokens_list = tokens_list->next;
	}
}

/**
 * get_next_pipe -
*/
token_ptr	get_next_pipe(token_ptr tokens_list)
{
	while (tokens_list)
	{
		tokens_list = tokens_list->next;
		if (tokens_list == NULL)
			break ;
		if (tokens_list->token_type == pipe_token)
			break ;
	}
	return (tokens_list);
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
