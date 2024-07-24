/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:35:58 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/24 01:28:05 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	new_token_lst(t_ptr tokens_list, int order, char *test)
{
	t_ptr	tmp;

	free(test);
	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->order == order)
		{
			free(tmp->token);
			tmp->token = ft_strdup("<");
			tmp->token_type = 8;
			return ;
		}
		tmp = tmp->next;
	}
}

t_bool	test(char **line, char *delimiter, int flag, int fd)
{
	while (1)
	{
		signal_handler_heredoc();
		*line = readline(">");
		if (*line == NULL)
			return (eof_printer(delimiter), true);
		if (*line[0] == '\0')
		{
			if (ft_strlen(delimiter) == 0)
			{
				g_global.ctrd = 1;
				return (false);
			}
			free(*line);
			write(fd, "\n", 1);
			continue ;
		}
		if (ft_strncmp(*line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(*line) == ft_strlen(delimiter))
			return (free(*line), true);
		if (flag == 0)
			*line = ft_expand_heredoc(*line, g_global.e);
		test_norm(fd, line);
	}
}

char	*heredoc_storer(char *delimiter, int i, t_env *envp, int flag)
{
	char	*filename;
	int		fd;
	char	*line;
	int		fd0;

	(void)envp;
	fd0 = dup(0);
	filename = get_unique_filename(i);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (test(&line, delimiter, flag, fd) == false)
		return (free(filename),line);
	close(fd);
	dup2(fd0, 0);
	close(fd0);
	if (line == NULL && g_global.flag == 1)
	{
		g_global.flag = 0;
		free(filename);
		return (NULL);
	}
	return (filename);
}

void	heredoc_norm(t_ptr tokens_list, int order, char *filename, int i)
{
	if (g_global.ctrd == 1)
		ft_enter(tokens_list, i);
	else
		filename_write(tokens_list, filename, order);
}

int	heredoc(t_ptr tmp, t_ptr tokens_list, t_env *envp)
{
	int		i;
	int		flag;
	char	*filename;
	char	*test;
	t_ptr	tmp2;

	i = 0;
	tmp2 = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 10)
		{
			flag = ft_no_expand(tmp);
			i++;
			test = ft_delimiter(tokens_list, tmp->order);
			filename = heredoc_storer(test, i, envp, flag);
			if (filename == NULL)
				return (free(test),1);
			new_token_lst(tokens_list, tmp->order, test);
			heredoc_norm(tokens_list, tmp->order, filename, i);
			free(filename);
		}
		tmp = tmp->next;
	}
	return (0);
}
