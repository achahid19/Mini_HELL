/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:46:43 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 00:16:04 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	first_pipe_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	if (tmp->token_type == 1)
	{
		print_error("kssh: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (tmp)
	{
		if (tmp->token_type == 1)
		{
			if (tmp->next == NULL || tmp->next->token_type == 1)
			{
				print_error("kssh: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	last_pipe_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->token_type == 1)
	{
		print_error("kssh: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (tmp->token_type == 1)
	{
		print_error("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	second_pipe_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	if (tmp->token_type == 0)
		while (tmp && tmp->token_type == 0)
			tmp = tmp->next;
	if (tmp->token_type == 1)
	{
		print_error("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	latest_pipe_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 1 && (tmp->previous->token_type == 8
				|| tmp->previous->token_type == 9
				|| tmp->previous->token_type == 10
				|| tmp->previous->token_type == 11))
		{
			print_error("minishell : syntax error near unexpected token `|'\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pipe_checker(t_ptr tokens_list)
{
	if (first_pipe_checker(tokens_list) == 1)
		return (1);
	if (second_pipe_checker(tokens_list) == 1)
		return (1);
	if (last_pipe_checker(tokens_list) == 1)
		return (1);
	if (latest_pipe_checker(tokens_list) == 1)
		return (1);
	return (0);
}
