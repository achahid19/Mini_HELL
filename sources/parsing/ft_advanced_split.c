/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:36:23 by aymane            #+#    #+#             */
/*   Updated: 2024/07/15 15:55:23 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	is_valid_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') 
            || (c >= '0' && c <= '9') || c == '_');
}

int	count_segments(const char *str)
{
	int	count;

	count = 0;
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

void	fill_segment(const char **str, char **result, int *index, char delimiter)
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

	segments = count_segments(str);
	result = (char **)malloc((segments + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	fill_segments(result, str);
	return (result);
}
