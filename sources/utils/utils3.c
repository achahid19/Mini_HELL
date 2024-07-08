/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:26:25 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/08 10:26:28 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	check_single_quotes(token_ptr node);

/**
 * check_single_quotes -
*/
t_bool	check_single_quotes(token_ptr node)
{
	if (node == NULL)
		return (false);
	else if (node->token_type == singlequote_token)
		return (true);
	return (false);
}
