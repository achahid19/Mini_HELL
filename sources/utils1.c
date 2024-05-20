/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:36:20 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/14 08:36:22 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

token_ptr	find_last_node(token_ptr head);
t_bool		ft_isspace(char c);

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
 * find_last_node - iterates over a linked list
 * to find the last node.
 * @head: pointer to the first node
 * 
 * Return: pointer to the last node.
*/
token_ptr	find_blast_node(token_ptr head)
{
	while (head != NULL)
	{
		if (head->next->next == NULL)
			break ;
		head = head->next;
	}
	return (head);
}
