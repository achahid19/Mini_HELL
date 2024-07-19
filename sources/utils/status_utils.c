/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:11:56 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/19 18:11:06 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include "../../includes/global.h"

void	dollar_status_check(token_ptr tokens_list);
char	*expand_status(char *tk, int *i);
int		get_length(char *tk);
void	before_tk_status(char *before, char *tk);
void	after_tk_status(char *after, char *tk);

/**
 * dolar_status_check -
*/
void	dollar_status_check(token_ptr tokens_list)
{
	int		i;
	char	*tk;
	t_bool	flag;
	char	*new_token;

	while (tokens_list)
	{
		i = 0;
		tk = tokens_list->token;
		while (tk[i] != '\0')
		{
			if (check_single_quotes(tokens_list->previous) == true)
				break ;
			if (tk[i] == '$' && tk[i + 1] == '?')
			{
				new_token = expand_status(tk, &i);
				free(tokens_list->token);
				tokens_list->token = new_token;
				tk = new_token;
			}
			i++;
		}
		tokens_list = tokens_list->next;
	}
}

/**
 * expand_status -
*/
char	*expand_status(char *tk, int *i)
{
	char	*st;
	char	*new_token;
	char	*before;
	char	*after;

	if (g_global.status == 256)
		g_global.status = 127;
	else if (g_global.status == 768)
		g_global.status = 1;
	else if (g_global.status == 32256)
		g_global.status = 126;
	else if (g_global.status == 512)
		g_global.status = 2;
	else if (g_global.status == 13)
		g_global.status = 0;
	st = ft_itoa(g_global.status);
	before = (char *)malloc(sizeof(char) * (*i) + 1);
	after = (char *)malloc(sizeof(char) * get_length(tk) + 1);
	before_tk_status(before, tk);
	after_tk_status(after, tk);
	before = ft_strjoin(before, st);
	before = ft_strjoin(before, after);
	new_token = before;
	free(after);
	free(st);
	return (new_token);
}

/**
 * get_length -
*/
int	get_length(char *tk)
{
	int	len;

	len = 0;
	while (*tk != '$' && *tk)
		tk++;
	if (*tk == '$')
		tk++;
	if (*tk == '?')
		tk++;
	while (*tk)
	{
		tk++;
		len++;
	}
	return (len);
}

/**
 * before_tk_status -
*/
void	before_tk_status(char *before, char *tk)
{
	int	i;

	i = 0;
	while (*tk)
	{
		if (*tk == '$' && *(tk + 1) == '?')
			break ;
		before[i] = *tk;
		tk++;
		i++;
	}
	before[i] = '\0';
}

/**
 * after_tk_status -
*/
void	after_tk_status(char *after, char *tk)
{
	size_t	i;

	i = 0;
	while (*tk)
	{
		if (*tk == '$' && *(tk + 1) == '?')
		{
			tk += 2;
			while (*tk)
			{
				after[i] = *tk;
				tk++;
				i++;
			}
			break ;
		}
		tk++;
	}
	after[i] = '\0';
}
