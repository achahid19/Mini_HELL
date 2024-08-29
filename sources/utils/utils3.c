/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:26:25 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/19 19:21:46 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	check_single_quotes(t_ptr node);
t_bool	builtin_checker(char *built_in);
void	open_output_fd(t_ptr *temp, t_var *data);
t_bool	check_quotes(t_var *d, t_ptr *tokens_list);
t_bool	space_trim(t_ptr tokens_list);

/**
 * check_single_quotes -
*/
t_bool	check_single_quotes(t_ptr node)
{
	if (node == NULL)
		return (false);
	else if (node->token_type == singlequote_token)
		return (true);
	return (false);
}

/**
 * builtin_checker -
*/
t_bool	builtin_checker(char *built_in)
{
	int	len;

	len = big_len(built_in, "echo");
	if (ft_strncmp(built_in, "echo", len) == 0)
		return (true);
	len = big_len(built_in, "cd");
	if (ft_strncmp(built_in, "cd", len) == 0)
		return (true);
	len = big_len(built_in, "pwd");
	if (ft_strncmp(built_in, "pwd", len) == 0)
		return (true);
	len = big_len(built_in, "export");
	if (ft_strncmp(built_in, "export", len) == 0)
		return (true);
	len = big_len(built_in, "unset");
	if (ft_strncmp(built_in, "unset", len) == 0)
		return (true);
	len = big_len(built_in, "env");
	if (ft_strncmp(built_in, "env", len) == 0)
		return (true);
	len = big_len(built_in, "exit");
	if (ft_strncmp(built_in, "exit", len) == 0)
		return (true);
	return (false);
}

/**
 * open_output_fd -
*/
void	open_output_fd(t_ptr *temp, t_var *data)
{
	if ((*temp)->token_type == rightred_token)
		data->fd[1] = open((*temp)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data->fd[1] = open((*temp)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd[1] == -1)
	{
		perror("\033[0;35mkssh");
		write(STDERR, "\033[0m", 4);
		free_close_child(data, data->av);
		exit(EXIT_FAILURE);
	}
}

/**
 * check_quotes -
*/
t_bool	check_quotes(t_var *d, t_ptr *tokens_list)
{
	d->tokens_list = *tokens_list;
	d->type = (*tokens_list)->token_type;
	if (d->type != doublequote_token && d->type != singlequote_token)
		return (false);
	return (true);
}

/**
 * space_trim -
 */
t_bool	space_trim(t_ptr tokens_list)
{
	while (tokens_list)
	{
		if (tokens_list->token_type != whitespace_token)
			break ;
		tokens_list = tokens_list->next;
	}
	if (tokens_list == NULL)
		return (true);
	return (false);
}
