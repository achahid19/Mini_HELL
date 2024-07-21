/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:20:30 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/20 21:20:31 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include "../../includes/global.h"

void	get_status();
void	split_words(token_ptr *tk_list);
void	add_nodes(token_ptr tk, char *word);
void	add_node(token_ptr tk, char *word, int type);

/**
 * get_status -
 */
void	get_status()
{
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
	else if (g_global.status == 127)
		g_global.status = 1;
}

/**
 * split_words -
 */
void	split_words(token_ptr *tk_list)
{
	token_ptr	tk;
	char		**word;
	int			i;

	tk = (*tk_list);
	while (tk)
	{
		if (tk->token_type == word_token)
		{
			word = ft_split(tk->token, ' ');
			i = 1;
			spliter(word, tk, &i);
			word = ft_split(tk->token, 9);
			i = 1;
			spliter(word, tk, &i);
		}
		tk = tk->next;
	}
}

/**
 * add_nodes -
 */
void	add_nodes(token_ptr tk, char *word)
{
	add_node(tk, " ", whitespace_token);
	add_node(tk, word, word_token);
	add_node(tk, " ", whitespace_token);
}

/**
 * add_word_node -
 */
void	add_node(token_ptr tk, char *word, int type)
{
	token_ptr	new;
	token_ptr	last;

	new = malloc(sizeof(t_token));
	new->token = ft_strdup(word);
	new->token_length = ft_strlen(new->token);
	new->previous = find_last_node(tk);
	new->token_type = type;
	if (new->previous != NULL)
		new->next = new->previous->next;
	last = find_last_node(tk);
	last->next = new;
}
