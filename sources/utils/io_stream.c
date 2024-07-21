/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_stream.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:27:46 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/19 18:10:40 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include "../../includes/global.h"

t_bool	input_red_stream(t_var *data);
t_bool	input_red_fd(token_ptr *temp, t_var *data);
t_bool	output_red_stream(t_var *data);
t_bool	output_red_fd(token_ptr *temp, t_var *data);
t_bool	output_red_helper(token_ptr *temp, t_var *data,
			t_bool *filename);

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
				break ;
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
				g_global.status = 1;
				return (false);
			}
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
			break ;
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
t_bool	output_red_stream(t_var *data)
{
	token_ptr	temp;

	temp = data->tokens_list;
	while (temp)
	{
		if (temp->token_type == rightred_token
			|| temp->token_type == append_token)
		{
			temp = temp->next;
			if (output_red_fd(&temp, data) == false)
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
				break ;
		}
	}
	return (true);
}

/**
 * output_red_fd -
*/
t_bool	output_red_fd(token_ptr *temp, t_var *data)
{
	static t_bool	filename;
	int				n;	

	if (filename == true)
		return (false);
	while (*temp)
	{
		n = output_red_helper(temp, data, &filename);
		if (n == false)
			break ;
		else if (n == 1337)
			return (false);
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
 * output_red_helper -
 */
t_bool	output_red_helper(token_ptr *temp, t_var *data,
			t_bool *filename)
{
	if (((*temp)->token_type == rightred_token
			|| (*temp)->token_type == append_token)
		&& ft_strncmp((*temp)->token, "", ft_strlen((*temp)->token))
		&& ft_strncmp((*temp)->token, ">", 1)
		&& ft_strncmp((*temp)->token, ">>", 2))
	{
		open_output_fd(temp, data);
		dup2(data->fd[1], STDOUT);
		close(data->fd[1]);
		return (false);
	}
	else if (((*temp)->token_type == rightred_token
			|| (*temp)->token_type == append_token))
	{
		print_error("kssh: ambigious redirect\n");
		*filename = true;
		return (1337);
	}
	return (true);
}
