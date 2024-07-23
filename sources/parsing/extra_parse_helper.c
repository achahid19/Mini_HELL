/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:19:17 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 00:26:52 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_valid_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| c == '?');
}

int	count_segments(const char *str, int count)
{
	while (*str)
	{
		if (*str == ' ')
		{
			count++;
			while (*str == ' ')
				str++;
		}
		else if (*str == '$')
		{
			count++;
			str++;
			while (*str && is_valid_char(*str))
				str++;
		}
		else
		{
			count++;
			while (*str && *str != ' ' && *str != '$')
				str++;
		}
	}
	return (count);
}

char	*allocate_segment(const char *start, int length)
{
	char	*segment;

	segment = (char *)malloc((length + 1) * sizeof(char));
	if (!segment)
		return (NULL);
	strncpy(segment, start, length);
	segment[length] = '\0';
	return (segment);
}

void	space_skip(t_ptr tokens_list)
{
	if (tokens_list->token_type == 0)
	{
		while (tokens_list->next && tokens_list->token_type == 0)
			tokens_list = tokens_list->next;
	}
}
