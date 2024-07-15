/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:26:25 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/15 21:20:00 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	check_single_quotes(token_ptr node);
t_bool	builtin_checker(char *built_in);
void	open_output_fd(token_ptr *temp, t_var *data);
t_bool	check_quotes(t_var *d, token_ptr *tokens_list);
t_bool	space_trim(token_ptr tokens_list);

/**
 * check_single_quotes -
*/
t_bool	check_single_quotes(token_ptr node)
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
	if (strncmp(built_in, "echo", ft_strlen(built_in)) == 0)
		return (true);
	if (strncmp(built_in, "cd", ft_strlen(built_in)) == 0)
		return (true);
	if (strncmp(built_in, "pwd", ft_strlen(built_in)) == 0)
		return (true);
	if (strncmp(built_in, "export", ft_strlen(built_in)) == 0)
		return (true);
	if (strncmp(built_in, "unset", ft_strlen(built_in)) == 0)
		return (true);
	if (strncmp(built_in, "env", ft_strlen(built_in)) == 0)
		return (true);
	if (strncmp(built_in, "exit", ft_strlen(built_in)) == 0)
		return (true);
	return (false);
}

/**
 * open_output_fd -
*/
void	open_output_fd(token_ptr *temp, t_var *data)
{
	if ((*temp)->token_type == rightred_token)
		data->fd[1] = open((*temp)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data->fd[1] = open((*temp)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd[1] == -1)
	{
		perror("\033[0;35mkssh");
		write(STDERR, "\033[0m", 4);
		exit(3);
	}
}

/**
 * check_quotes -
*/
t_bool	check_quotes(t_var *d, token_ptr *tokens_list)
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
t_bool	space_trim(token_ptr tokens_list)
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
