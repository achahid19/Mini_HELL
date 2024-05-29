/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_data_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:14:32 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/29 13:14:33 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	move_data(t_expand *data, char *dollar_tk, char *token);
void	data_move_helper(t_expand *data, char **token);


/**
 * move-data -
*/
void	move_data(t_expand *data, char *dollar_tk, char *token)
{
	data->i = 0;
	data->flag = false;
	while (data->i < data->new_tk_len)
	{
		
		if (*token != '$')
			data_move_helper(data, &token);
		else if (*token == '$' && data->flag == 0 && *(token + 1) != '$'
				&& (ft_isalpha(*(token + 1)) || *(token + 1) == '_'))
		{
			data->flag = true;
			while (data->tmp_tk_len-- >= 0)
				token++;
				while (data->dollar_tk_len--)
			{
				data->new_token[data->i] = *dollar_tk;
				dollar_tk++;
				data->i++;
			}
		}
		else
			data_move_helper(data, &token);
	}
	data->new_token[data->i] = '\0';
}

/**
 * data_move_helper -
*/
void	data_move_helper(t_expand *data, char **token)
{
	data->new_token[data->i] = token[0][0];
	*token += 1;
	data->i++;
}
