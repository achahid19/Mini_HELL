/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:20:09 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/23 23:18:05 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	pipe_order_check(t_ptr *tokens_list);
void	pipe_node_remover(t_ptr *last);
void	child_exec_helper(t_var *data, char **av);
void	spliter(char **word, t_ptr tk, int *i);
void	set_tk_exp_len(t_ptr *tokens_list);

/**
 * pipe_order_check -
 */
void	pipe_order_check(t_ptr *tokens_list)
{
	t_ptr	last;

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
void	pipe_node_remover(t_ptr *last)
{
	t_ptr	to_free;

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
	if (av[0][0] == '.')
		data->path_to_cmd = av[0];
	if (data->path_to_cmd != NULL)
	{
		if (execve(data->path_to_cmd, av, data->envp) == -1)
			exit_error(" command not found !\n", data, av, EXIT_FAILURE);
	}
	else
		exit_error(" command not found !\n", data, av, EXIT_FAILURE);
}

/**
 * spliter -
*/
void	spliter(char **word, t_ptr tk, int *i)
{
	if (word[*i] != NULL)
	{
		free(tk->token);
		tk->token = ft_strdup(word[0]);
	}
	while (word[*i] != NULL)
	{
		add_nodes(tk, word[*i]);
		*i += 1;
	}
	free_cmd_table(word);
}

/**
 * set_tk_exp_len -
*/
void	set_tk_exp_len(t_ptr *tokens_list)
{
	(*tokens_list)->token_length = ft_strlen((*tokens_list)->token);
	if ((*tokens_list)->token_length == 0)
		(*tokens_list)->token_type = filename_tk;
}
