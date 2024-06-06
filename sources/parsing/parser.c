/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/06 18:12:17 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"


int    ft_type_check(token_ptr tokens_list)
{
	if (pipe_checker(tokens_list) == 1)
		return 1;
	if (redirections_checker(tokens_list) == 1)
		return 1;
	if (semicolon_checker(tokens_list) == 1)
		return 1;
	if (backslash_checker(tokens_list) == 1)
		return 1;
	if (parentheses_checker(tokens_list) == 1)
		return 1;
	if (heredoc_append_checker(tokens_list) == 1)
		return 1;
	return 0;
}

int	parser_tokens(token_ptr tokens_list)
{
	if (tokens_list == NULL)
		return  0;
	if (ft_type_check(tokens_list) == 1)
		return 1;
	//build_in(tokens_list);
	return 0;
}
