/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:20:09 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/21 14:20:10 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	pipe_order_check(token_ptr *tokens_list);
void	pipe_node_remover(token_ptr *last);
void	child_exec_helper(t_var *data, char **av);

/**
 * pipe_order_check -
 */
void	pipe_order_check(token_ptr *tokens_list)
{
	token_ptr	last;
	token_ptr	begin;

	if (*tokens_list == NULL)
		return ;
	last = find_last_node((*tokens_list));
	while (last->token_type == pipe_token)
	{
		if (last->previous == NULL)
			*tokens_list = NULL;
		pipe_node_remover(&last);
		if (last == NULL)
			break ;
	}
}

/**
 * pipe_node_remover -
 */
void	pipe_node_remover(token_ptr *last)
{
	token_ptr	to_free;

	to_free = (*last);
	free((*last)->token);
	(*last) = (*last)->previous;
	if ((*last))
		(*last)->next = NULL;
	free(to_free);
}

/**
 * child_exec_helper -
 */
void	child_exec_helper(t_var *data, char **av)
{
	if (ft_strncmp(av[0], "/", 1) == 0)
	{
		data->path_to_cmd = av[0];
		points_checker(*data, av);
		if (access(data->path_to_cmd, X_OK) == 0)
		{
			if (execve(data->path_to_cmd, av, data->envp) == -1)
				exit_error(" No such file or directory !\n", data, av,
					126);
		}
		else
			exit_error(" No such file or directory !\n", data, av,
				EXIT_FAILURE);
	}
	
	data->path_to_cmd = ft_find_cmd(av[0], data->envp);
	if (data->path_to_cmd == NULL)
		data->path_to_cmd = av[0];
	if (execve(data->path_to_cmd, av, data->envp) == -1)
		exit_error(" command not found !\n", data, av, EXIT_FAILURE);
}

/**
 * space_last_skip -
 */
/* void	space_last_skip(token_ptr *last)
{
	while ((*last)->token_type == whitespace_token)
	{
		(*last) = (*last)->previous;
		if ((*last) == NULL)
			return ;
	}
} */
