/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 08:59:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/13 08:59:48 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	quotes_substitut(char **cmd_table);
void	close_fds(t_var *data);

/**
 * quotes_substitut -
*/
void	quotes_substitut(char **cmd_table)
{
	size_t	i;

	if (!cmd_table || !*cmd_table)
		return ;
	i = 1;
	while (cmd_table[i])
	{
		if (ft_strncmp(cmd_table[i], "\"\"", ft_strlen(cmd_table[i])) == 0
			|| ft_strncmp(cmd_table[i], "''", ft_strlen(cmd_table[i])) == 0)
		{
			free(cmd_table[i]);
			cmd_table[i] = malloc(1);
			cmd_table[i][0] = '\0';
		}
		i++;
	}
}

/**
 * close_fds -
*/
void	close_fds(t_var *data)
{
	if (data->fd[0] != false)
		close(data->fd[0]);
	if (data->fd[1] != false)
		close(data->fd[1]);
	if (data->end[0] != false)
		close(data->end[0]);
	if (data->end[1] != false)
		close(data->end[1]);
}
