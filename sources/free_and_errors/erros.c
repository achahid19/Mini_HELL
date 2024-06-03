/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:09:42 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/03 16:09:44 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

/**
 * quotes_error -
*/
void	quotes_error(int type)
{
	if (type == doublequote_token)
		ft_putstr_fd("bash: Error for double quotes\n", 2);
	else if (type == singlequote_token)
		ft_putstr_fd("bash: Error for single quotes\n", 2);
}
