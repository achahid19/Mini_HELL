/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:28:02 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 00:33:31 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_ptr	find_last_node2(t_ptr list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	eof_printer(char *delimiter)
{
	if (g_global.flag == 1)
		return ;
	if (delimiter[0] == '\0')
	{
		g_global.ctrd = 1;
		delimiter = "";
	}
	printf("warning: here-document at line %d", g_global.eof++);
	printf(" delimited by end-of-file (wanted `%s')\n", delimiter);
}

int	ft_no_expand(t_ptr tmp)
{
	t_ptr	tmp2;

	tmp2 = tmp->next;
	while (tmp2)
	{
		if (tmp2->token_type == 8 || tmp2->token_type == 9
			|| tmp2->token_type == 10 || tmp2->token_type == 11)
			break ;
		if (tmp2->token_type == 4 || tmp2->token_type == 5)
			return (1);
		tmp2 = tmp2->next;
	}
	return (0);
}

void	ft_enter(t_ptr tokens_list, int i)
{
	t_ptr	tmp;
	char		*filename;

	g_global.ctrd = 0;
	filename = get_unique_filename(i);
	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 4 || tmp->token_type == 5)
		{
			tmp->token = ft_strdup(filename);
			tmp->token_type = 2;
			free(filename);
			break ;
		}
		tmp = tmp->next;
	}
}

void	test_norm(int fd, char **line)
{
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
}
