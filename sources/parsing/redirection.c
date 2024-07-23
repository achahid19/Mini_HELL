/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:59:00 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 21:16:30 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	redirections_checker_1(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 8 || tmp->token_type == 9
			|| tmp->token_type == 11)
		{
			if (tmp->next == NULL || tmp->next->token_type == 8
				|| tmp->next->token_type == 9)
				return (print_error
					("syntax error near unexpected token `newline'\n"), 1);
			else if (tmp->next->token_type == 5 || tmp->next->token_type == 4)
			{
				if (tmp->next->next->next == NULL)
				{
					print_error(": : No such file or directory\n");
					return (1);
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirections_checker_2(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	if ((tmp->token_type == 8 || tmp->token_type == 9)
		&& (tmp->next->token_type == 8 || tmp->next->token_type == 9))
	{
		if (tmp->next->token_type == 8)
		{
			print_error("syntax error near unexpected token `<'\n");
			return (1);
		}
		else
		{
			print_error("syntax error near unexpected token `>'\n");
			return (1);
		}
	}
	return (0);
}

int	redirections_checker_3(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 8 || tmp->token_type == 9)
		{
			if (tmp->next->token_type == 10 || tmp->next->token_type == 11)
			{
				if (tmp->next->token_type == 10)
					print_error("syntax error near unexpected token `<<'\n");
				else
					print_error("syntax error near unexpected token `>>'\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirections_checker(t_ptr tokens_list)
{
	if (redirections_checker_1(tokens_list) == 1)
		return (1);
	if (redirections_checker_2(tokens_list) == 1)
		return (1);
	if (redirections_checker_3(tokens_list) == 1)
		return (1);
	return (0);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
