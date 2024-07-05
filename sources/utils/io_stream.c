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

t_bool	input_red_stream(t_var data);
t_bool	input_red_fd(token_ptr *temp);

/**
 * input_red_check -
*/
t_bool	input_red_stream(t_var data)
{
	token_ptr	temp;

	temp = data.tokens_list;
	while (temp)
	{
		if (temp->token_type == leftred_token)
		{
			temp = temp->next;
			if (input_red_fd(&temp) == false)
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
t_bool	input_red_fd(token_ptr *temp)
{
	int	fd;

	while (*temp)
	{
		if ((*temp)->token_type == leftred_token)
		{
			fd = open((*temp)->token, O_RDONLY);
			if (fd == -1)
			{
				print_error("kssh: No such file or directory\n");
				return (false);
			}
			dup2(fd, STDIN_FILENO);
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
/* void	output_red_stream(t_var data)
{
	token_ptr	temp;

	temp = data.tokens_list;
	while (temp)
	{
		if (temp->token_type == rightred_token)
		{
			temp = temp->next;
		}
	}
} */
