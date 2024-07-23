/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:36:23 by aymane            #+#    #+#             */
/*   Updated: 2024/07/23 00:26:05 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	fill_segment(const char **str, char **result, int *index,
		char delimiter)
{
	const char	*start;
	int			length;

	start = *str;
	while (**str && **str != delimiter && **str != '$')
		(*str)++;
	length = *str - start;
	result[*index] = allocate_segment(start, length);
	(*index)++;
}

void	fill_space_segment(const char **str, char **result, int *index)
{
	const char	*start;
	int			length;

	start = *str;
	while (**str == ' ')
		(*str)++;
	length = *str - start;
	result[*index] = allocate_segment(start, length);
	(*index)++;
}

void	fill_dollar_segment(const char **str, char **result, int *index)
{
	const char	*start;
	int			length;

	start = *str;
	(*str)++;
	while (**str && is_valid_char(**str))
		(*str)++;
	length = *str - start;
	result[*index] = allocate_segment(start, length);
	(*index)++;
}

void	fill_segments(char **result, const char *str)
{
	int	index;

	index = 0;
	while (*str)
	{
		if (*str == ' ')
			fill_space_segment(&str, result, &index);
		else if (*str == '$')
			fill_dollar_segment(&str, result, &index);
		else
			fill_segment(&str, result, &index, ' ');
	}
	result[index] = NULL;
}

char	**ft_advanced_split(const char *str)
{
	int		segments;
	char	**result;
	int		count;

	count = 0;
	segments = count_segments(str, count);
	result = (char **)malloc((segments + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	fill_segments(result, str);
	return (result);
}
