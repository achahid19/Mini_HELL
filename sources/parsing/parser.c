/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/21 19:17:55 by akajjou          ###   ########.fr       */
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

token_ptr	find_last_node2(token_ptr list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

token_ptr	copy_tokens(token_ptr tokens_list)
{
	token_ptr	tmp;
	token_ptr	new_list;
	token_ptr	new_node;
	token_ptr	last_node;

	tmp = tokens_list;
	new_list = NULL;
	while (tmp)
	{
		if (tmp->token_type == 0)
		{
			tmp = tmp->next;
			continue;
		}
		new_node = (token_ptr)malloc(sizeof(t_token));
		new_node->token = ft_strdup(tmp->token);
		new_node->token_type = tmp->token_type;
		new_node->order = tmp->order;
		new_node->token_length = tmp->token_length;
		new_node->next = NULL;
		new_node->previous = NULL;
		if (!new_list)
			new_list = new_node;
		else
		{
			last_node = find_last_node2(new_list);
			last_node->next = new_node;
			new_node->previous = last_node;
		}
		tmp = tmp->next;
	}
	return (new_list);
}

int	parser_tokens(token_ptr tokens_list, t_env *env)
{
	token_ptr tmp;
	
	tmp = copy_tokens(tokens_list);
	if (tmp == NULL)
		return  true;
	if (ft_type_check(tmp) == 1)
	{
		g_global.status = 2;
		get_status();
		free_tokens(tmp);
		return false;
	}
	heredoc(tmp,tokens_list,env);
	free_tokens(tmp);
	return true;
}
// kssh$ <<>>ls
// kssh$ <<ls<ls


