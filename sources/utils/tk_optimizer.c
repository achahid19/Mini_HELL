/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_optimizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 04:29:05 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/11 04:29:06 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	node_remover(t_ptr *node);				
void	special_chars_refactor(t_ptr tokens_list);
t_bool	special_chars_finder(t_ptr *tokens_list, t_ptr node_add,
				int type);
t_bool	special_chars_type(t_ptr *tokens_list, int type);

/**
 * node_remover -
*/
void	node_remover(t_ptr *node)
{
	t_ptr	tmp;
	t_ptr	free_node;
	t_ptr	previous;

	tmp = *node;
	free_node = tmp;
	previous = tmp->previous;
	tmp = tmp->next;
	if (previous != NULL)
		previous->next = tmp;
	else
		*node = tmp;
	if (tmp != NULL)
		tmp->previous = previous;
	if (previous == NULL && tmp == NULL)
		*node = NULL;
	*node = (*node)->next;
	free(free_node->token);
	free(free_node);
	free_node = NULL;
}

/**
 * special_chars_refactor -
 */
void	special_chars_refactor(t_ptr tokens_list)
{
	int			type;
	t_ptr	node_add;

	while (tokens_list)
	{
		type = tokens_list->token_type;
		if (special_chars_checker(type) == true)
		{
			if (special_chars_type(&tokens_list, type) == false)
				return ;
			node_add = tokens_list;
			if (special_chars_finder(&tokens_list, node_add, type) == false)
				return ;
		}
		tokens_list = tokens_list->next;
		if (tokens_list == NULL)
			return ;
		if (tokens_list->token_type == pipe_token)
			return ;
	}
}

/**
 * special_chars_type -
*/
t_bool	special_chars_type(t_ptr *tokens_list, int type)
{
	(*tokens_list) = (*tokens_list)->next;
	if ((*tokens_list) == NULL)
		return (false);
	while ((*tokens_list)->token_type != (t_type)type)
	{
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) == NULL)
			return (false);
	}
	return (true);
}

/**
 * special_chars_finder -
*/
t_bool	special_chars_finder(t_ptr *tokens_list, t_ptr node_add,
			int type)
{
	while (type != whitespace_token && type != pipe_token)
	{
		if (type == string_token || type == word_token || type == cmd)
		{
			node_add->token = ft_strjoin(node_add->token,
					(*tokens_list)->token);
			node_remover(tokens_list);
		}
		if ((*tokens_list) == NULL)
			return (false);
		if ((*tokens_list)->token_type == whitespace_token)
			return (true);
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) == NULL)
			return (false);
		type = (*tokens_list)->token_type;
	}
	return (true);
}
