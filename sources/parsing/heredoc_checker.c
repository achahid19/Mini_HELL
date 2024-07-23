/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:13:04 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 22:10:30 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	heredoc_checker_first(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 10)
		{
			if (tmp->next == NULL || tmp->next->token_type == 10
				|| tmp->next->token_type == 8 || tmp->next->token_type == 9
				|| tmp->next->token_type == 11)
			{
				print_error("syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	append_checker_second(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 11)
		{
			if (tmp->next == NULL || tmp->next->token_type == 10
				|| tmp->next->token_type == 8 || tmp->next->token_type == 9
				|| tmp->next->token_type == 11)
			{
				print_error("syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc_max_checker(t_ptr tokens_list)
{
	int			count;
	t_ptr		tmp;

	count = 0;
	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 10)
			count++;
		tmp = tmp->next;
	}
	if (count > 16)
	{
		print_error("minishell : maximum here-document count exceeded\n");
		return (1);
	}
	return (0);
}

int	heredoc_next_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp && tmp->next)
	{
		if (tmp->token_type == 10 && (tmp->next->token_type == 10
				|| tmp->next->token_type == 8 || tmp->next->token_type == 9))
		{
			print_error("syntax error near unexpected token`newline'\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc_append_checker(t_ptr tokens_list)
{
	if (heredoc_checker_first(tokens_list) == 1)
		return (1);
	if (append_checker_second(tokens_list) == 1)
		return (1);
	if (heredoc_max_checker(tokens_list) == 1)
		return (1);
	if (heredoc_next_checker(tokens_list) == 1)
		return (1);
	return (0);
}
