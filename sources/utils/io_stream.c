/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_stream.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:27:46 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/05 06:27:49 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	input_red_stream(t_var *data);
t_bool	input_red_fd(token_ptr *temp, t_var *data);
void	output_red_stream(t_var *data);
void	output_red_fd(token_ptr *temp, t_var *data);

/**
 * input_red_check -
*/
t_bool	input_red_stream(t_var *data)
{
	token_ptr	temp;

	temp = data->tokens_list;
	while (temp)
	{
		if (temp->token_type == leftred_token)
		{
			temp = temp->next;
			if (input_red_fd(&temp, data) == false)
				return (false);
			if (temp == NULL)
				break ;
			else if (temp->token_type == pipe_token)
				break ;
		}
		temp = temp->next;
		if (temp != NULL)
		{
			if (temp->token_type == pipe_token)
				break;
		}
	}
	return (true);
}

/**
 * input_red_fd -
*/
t_bool	input_red_fd(token_ptr *temp, t_var *data)
{
	while (*temp)
	{
		if ((*temp)->token_type == leftred_token)
		{
			data->fd[0] = open((*temp)->token, O_RDONLY);
			if (data->fd[0] == -1)
			{
				print_error("kssh: No such file or directory\n");
				return (false);
			}
			dup2(data->fd[0], STDIN_FILENO);
			break;
		}
		(*temp) = (*temp)->next;
		if ((*temp) != NULL)
		{
			if ((*temp)->token_type == pipe_token)
				break ;
		}
	}
	return (true);
}

/**
 * output_red_stream -
*/
void	output_red_stream(t_var *data)
{
	token_ptr	temp;

	temp = data->tokens_list;
	while (temp)
	{
		if (temp->token_type == rightred_token
			|| temp->token_type == append_token)
		{
			int fd;
			temp = temp->next;
			output_red_fd(&temp, data);
			if (temp == NULL)
				break ;
			else if (temp->token_type == pipe_token)
				break ;
		}
		temp = temp->next;
		if (temp != NULL)
		{
			if (temp->token_type == pipe_token)
				break;
		}
	}
}

/**
 * output_red_fd -
*/
void	output_red_fd(token_ptr *temp, t_var *data)
{
	while (*temp)
	{
		if ((*temp)->token_type == rightred_token
			|| (*temp)->token_type == append_token)
		{
			if ((*temp)->token_type == rightred_token)
				data->fd[1] = open((*temp)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				data->fd[1] = open((*temp)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (data->fd[1] == -1)
			{
				print_error("kssh: No such file or directory\n");
				exit(EXIT_FAILURE);
			}
			dup2(data->fd[1], STDOUT);
			break;
		}
		(*temp) = (*temp)->next;
		if ((*temp) != NULL)
		{
			if ((*temp)->token_type == pipe_token)
				break ;
		}
	}
}
