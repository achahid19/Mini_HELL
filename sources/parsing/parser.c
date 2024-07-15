/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/13 18:49:40 by aymane           ###   ########.fr       */
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

int	parser_tokens(token_ptr tokens_list, t_env *env)
{
	token_ptr tmp;
	
	tmp = copy_tokens(tokens_list);
	if (tmp == NULL)
		return  true;
	if (ft_type_check(tmp) == 1)
		return false;
	// exit(0);
	heredoc(tmp,tokens_list,env);
	return true;
}
// kssh$ <<>>ls
// kssh$ <<ls<ls


