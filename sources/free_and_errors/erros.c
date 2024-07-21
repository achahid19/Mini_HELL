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
#include "../../includes/global.h"

void	print_error(char *error);
void	quotes_error(int type);

/**
 * print_error -
*/
void	print_error(char *error)
{
	write(STDERR, "\033[0;35m", 7);
	write(STDERR, error, ft_strlen(error));
	write(STDERR, "\033[0m", 4);
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

/**
 * exit_error -
*/
void	exit_error(char *error, t_var *data, char **av, int ex_code)
{
	print_error("kssh: ");
	print_error("'");
	print_error(data->path_to_cmd);
	print_error("'");
	print_error(error);
	free_all(data->tokens_list, data->user_input, av);
	free_global_env();
	exit(ex_code);
}
