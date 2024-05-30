/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:59:00 by akajjou           #+#    #+#             */
/*   Updated: 2024/05/26 21:43:17 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	redirections_checker(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 9 || tmp->token_type == 8)
		{
			if (tmp->next && tmp->next->token_type == 0)
				while (tmp->next && tmp->next->token_type == 0)
					tmp = tmp->next;
			if (tmp->next == NULL || tmp->next->token_type == 9
				|| tmp->next->token_type == 8)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
						2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
