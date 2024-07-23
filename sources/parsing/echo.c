/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:18:40 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 19:51:06 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	semicolon_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (ft_strchr(tmp->token, ';') != NULL && tmp->token_type != 3)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `;'\n",
				2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	backslash_checker(t_ptr tokens_list)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (ft_strchr(tmp->token, '\\') != NULL)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `\\'\n",
				2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_unique_filename(int i)
{
	char	*filename;
	char	*num;

	num = ft_itoa(i);
	filename = ft_strdup("/tmp/heredoc_");
	filename = ft_strjoin(filename, num);
	free(num);
	return (filename);
}

void	filename_write(t_ptr tokens_list, char *filename, int order)
{
	t_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->order == order)
		{
			ft_eraser(tmp, filename);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_eraser(t_ptr tmp, char *filename)
{
	t_ptr	tmp2;

	tmp2 = tmp->next;
	if (tmp2->token_type == 0)
		while (tmp2 && tmp2->token_type == 0)
			tmp2 = tmp2->next;
	while (tmp2 && tmp2->token_type != 20)
		node_remover(&tmp2);
	free(tmp2->token);
	tmp2->token = ft_strdup(filename);
	tmp2 = tmp2->next;
	while (tmp2 && tmp2->token_type != 0 && tmp2->token_type != 1
		&& tmp2->token_type != 8 && tmp2->token_type != 9
		&& tmp2->token_type != 10 && tmp2->token_type != 11)
		node_remover(&tmp2);
	tmp2 = tmp;
	while (tmp2)
	{
		if (tmp2->token_type == 20)
			tmp2->token_type = 2;
		tmp2 = tmp2->next;
	}
}
