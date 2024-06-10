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
t_bool		type_checker(int type);
token_ptr	get_next_pipe(token_ptr tokens_list);

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
 * type_checker -
*/
t_bool	type_checker(int type)
{
	return (type == heredoc_token || type == leftred_token ||
			type == rightred_token || type == append_token);
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
