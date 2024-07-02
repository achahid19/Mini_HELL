/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/02 07:03:26 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"

void	space_skip(token_ptr tokens_list)
{
	if (tokens_list->token_type == 0)
	{
		while (tokens_list->next && tokens_list->token_type == 0)
			tokens_list = tokens_list->next;
	}
}

int    ft_type_check(token_ptr tokens_list)
{
	if (pipe_checker(tokens_list) == 1)
		return 1;
	if (redirections_checker(tokens_list) == 1)
		return 1;
	if (heredoc_append_checker(tokens_list) == 1)
		return 1;
	return 0;
}

token_ptr 	copy_tokens(token_ptr tokens_list)
{
	token_ptr tmp = tokens_list;
	token_ptr new_list = NULL;
	token_ptr new_node = NULL;
	while (tmp)
	{
		if (tmp->token_type == 0)
		{
			tmp = tmp->next;
			continue;
		}
		new_node = (token_ptr)malloc(sizeof(struct s_token));
		new_node->token = ft_strdup(tmp->token);
		new_node->token_type = tmp->token_type;
		new_node->order = tmp->order;
		new_node->next = NULL;
		new_node->previous = NULL;
		if (new_list == NULL)
		{
			new_list = new_node;
			new_list->next = NULL;
			new_list->previous = NULL;
		}
		else
		{
			new_node->previous = find_last_node(new_list);
			new_node->previous->next = new_node;
		}
		tmp = tmp->next;		
	}
	return new_list;
}
char	*heredoc_storer(char *delimiter, int i)
{
	char *filename;
	int fd;
	char *line;

	filename = get_unique_filename(i);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return filename;
}
void	heredoc(token_ptr tmp, token_ptr tokens_list)
{
	token_ptr tmp2 = tokens_list;
	int i = 0;
	char *filename;
	while (tmp)
	{
		if (tmp->token_type == 10)
		{
			i++;
			filename = heredoc_storer(tmp->next->token, i);
			new_token_lst(tokens_list,tmp->order);
			filename_write(tokens_list, filename, tmp->order);
		}
		tmp = tmp->next;
	}
}


int	parser_tokens(token_ptr tokens_list)
{
	token_ptr tmp;
	
	tmp = copy_tokens(tokens_list);
	if (tokens_list == NULL)
		return  true;
	if (ft_type_check(tmp) == 1)
		return false;
	heredoc(tmp,tokens_list);
	// check_tokens(tokens_list);
	// exit(0);
	return true;
}
// kssh$ <<>>ls
// kssh$ <<ls<ls


