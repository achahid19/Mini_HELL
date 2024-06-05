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
<<<<<<< HEAD
		ft_putstr_fd("\033[0;35mkssh: Error double quotes\n\033[0m"
			, STDERR);
	else if (type == singlequote_token)
		ft_putstr_fd("\033[0;35mkssh: Error single quotes\n\033[0m"
			, STDERR);
=======
		ft_putstr_fd("bash: Error for double quotes\n", STDERR);
	else if (type == singlequote_token)
		ft_putstr_fd("bash: Error for single quotes\n", STDERR);
>>>>>>> master
}
