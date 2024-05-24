/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:13:15 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/24 11:13:16 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

/**
 * string_hanlder - handle the execution of the
 * expansion of dollar sign, in double quoted string
*/
t_bool	string_handler(token_ptr *tokens_list)
{
	if ((*tokens_list)->token_type == doublequote_token)
	{
		*tokens_list = (*tokens_list)->next;
		if ((*tokens_list) == NULL
			|| (*tokens_list)->token_type == doublequote_token)
			return (false);
	}
	return (true);
}
