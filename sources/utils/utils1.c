/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:36:20 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/24 18:37:47 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

token_ptr		find_last_node(token_ptr head);
t_bool			ft_isspace(char c);
char			*ft_realloc(char *to_free, int new_len);
void			tokens_list_optimizer(token_ptr *tokens_list);
static void		whitespace_remover(token_ptr *tokens_list,
					token_ptr free_node, token_ptr previous);

/**
 * find_last_node - iterates over a linked list
 * to find the last node.
 * @head: pointer to the first node
 * 
 * Return: pointer to the last node.
*/
token_ptr	find_last_node(token_ptr head)
{
	while (head != NULL)
	{
		if (head->next == NULL)
			break ;
		head = head->next;
	}
	return (head);
}

/**
 * ft_isspace - checks if the character c
 * is a space or not.
 * @c: character
 * 
 * Return: boolean.
*/
t_bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/**
 * ft_realloc -
*/
char	*ft_realloc(char *to_free, int new_len)
{
	char	*new_ptr;

	free(to_free);
	new_ptr = (char *)malloc(sizeof(char) * new_len + 1);
	return (new_ptr);
}

/**
 * tokens_list_optimizer -
*/
void	tokens_list_optimizer(token_ptr *tokens_list)
{
	token_ptr	tmp;
	token_ptr	free_node;
	token_ptr	previous;

	tmp = *tokens_list;
	free_node = NULL;
	previous = NULL;
	whitespace_remover(tokens_list, free_node, previous);
	if (*tokens_list != NULL)
		check_tokens(*tokens_list);
}

/**
 * whitespace_remover -
*/
static void	whitespace_remover(token_ptr *tokens_list,
				token_ptr free_node, token_ptr previous)
{
	token_ptr	tmp;

	tmp = *tokens_list;
	while (tmp)
	{
		if (tmp->token_type == whitespace_token || tmp->token_length == 0)
		{
			free_node = tmp;
			previous = tmp->previous;
			tmp = tmp->next;
			if (previous != NULL)
				previous->next = tmp;
			else
				*tokens_list = tmp;
			if (tmp != NULL)
				tmp->previous = previous;
			if (previous == NULL && tmp == NULL)
				*tokens_list = NULL;
			free(free_node->token);
			free(free_node);
			free_node = NULL;
			continue ;
		}
		tmp = tmp->next;
	}
}
