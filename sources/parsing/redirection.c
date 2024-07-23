/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:59:00 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 20:18:10 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	redirections_checker_1(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 8 || tmp->token_type == 9
			|| tmp->token_type == 11)
		{
			if (tmp->next == NULL || tmp->next->token_type == 8
				|| tmp->next->token_type == 9)
				return (print_error
					("syntax error near unexpected token `newline'\n"), 1);
			else if (tmp->next->token_type == 5 || tmp->next->token_type == 4)
			{
				if (tmp->next->next->next == NULL)
				{
					print_error(": : No such file or directory\n");
					return (1);
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirections_checker_2(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	if ((tmp->token_type == 8 || tmp->token_type == 9)
		&& (tmp->next->token_type == 8 || tmp->next->token_type == 9))
	{
		if (tmp->next->token_type == 8)
		{
			print_error("syntax error near unexpected token `<'\n");
			return (1);
		}
		else
		{
			print_error("syntax error near unexpected token `>'\n");
			return (1);
		}
	}
	return (0);
}

int	redirections_checker_3(token_ptr tokens_list)
{
	token_ptr	tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 8 || tmp->token_type == 9)
		{
			if (tmp->next->token_type == 10 || tmp->next->token_type == 11)
			{
				if (tmp->next->token_type == 10)
					print_error("syntax error near unexpected token `<<'\n");
				else
					print_error("syntax error near unexpected token `>>'\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirections_checker(token_ptr tokens_list)
{
	if (redirections_checker_1(tokens_list) == 1)
		return (1);
	if (redirections_checker_2(tokens_list) == 1)
		return (1);
	if (redirections_checker_3(tokens_list) == 1)
		return (1);
	return (0);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}


