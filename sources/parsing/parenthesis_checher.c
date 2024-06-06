/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_checher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:35:45 by akajjou           #+#    #+#             */
/*   Updated: 2024/06/06 20:35:38 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"

int		parentheses_checker(token_ptr tokens_list)
{
	token_ptr	tmp;
	int			open;
	int			close;

	tmp = tokens_list;
	open = 0;
	close = 0;
	while (tmp)
	{
		if (ft_strchr(tmp->token, '(') != NULL && tmp->token_type != 3)
			open++;
		if (ft_strchr(tmp->token, ')') != NULL && tmp->token_type != 3)
			close++;
		tmp = tmp->next;
	}
	if (open != close)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		return 1;
	}
	return 0;
}
