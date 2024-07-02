/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:09:42 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/02 03:39:42 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	print_error(char *error);
void	quotes_error(int type);

/**
 * print_error -
*/
void	print_error(char *error)
{
	write(STDERR, "\033[0;35m", 7);
	write(STDERR, error, ft_strlen(error));
	write(STDERR, "\033[0m",4);
	write(STDERR, "\n", 1);
}

/**
 * quotes_error -
*/
void	quotes_error(int type)
{
	if (type == doublequote_token)
		print_error("kssh: Error double quotes\n");
	else if (type == singlequote_token)
		print_error("kssh: Error single quotes\n");
}
