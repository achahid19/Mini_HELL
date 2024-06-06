/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:13:04 by akajjou           #+#    #+#             */
/*   Updated: 2024/06/06 18:13:18 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"

int		heredoc_checker_first(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 10)
		{
			if (tmp->next == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return 1;
			}
			if (tmp->next->token_type == 0)
				while (tmp->next->token_type == 0)
				{
					tmp = tmp->next;
					if (tmp->next == NULL)
					{
						ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
						return 1;
					}
				}
		}
		tmp = tmp->next;
	}
	return 0;
}
int		append_checker_second(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 11)
		{
			if (tmp->next == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return 1;
			}
			if (tmp->next->token_type == 0)
				while (tmp->next->token_type == 0)
				{
					tmp = tmp->next;
					if (tmp->next == NULL)
					{
						ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
						return 1;
					}
				}
		}
		tmp = tmp->next;
	}
	return 0;
}

int     heredoc_append_checker(token_ptr tokens_list)
{
    if (heredoc_checker_first(tokens_list) == 1)
        return 1;
    if (append_checker_second(tokens_list) == 1)
        return 1;
    return 0;
}