/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:20:30 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/23 22:12:51 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include "../../includes/global.h"

void	split_words(t_ptr *tk_list);
void	add_nodes(t_ptr tk, char *word);
void	add_node(t_ptr tk, char *word, int type);
void	io_dup_close(t_var *data);
void	status_handle(void);

/**
 * split_words -
 */
void	split_words(t_ptr *tk_list)
{
	t_ptr		tk;
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
void	add_nodes(t_ptr tk, char *word)
{
	add_node(tk, " ", whitespace_token);
	add_node(tk, word, word_token);
	add_node(tk, " ", whitespace_token);
}

/**
 * add_word_node -
 */
void	add_node(t_ptr tk, char *word, int type)
{
	t_ptr	new;
	t_ptr	last;

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

/**
 * io_dup_close -
*/
void	io_dup_close(t_var *data)
{
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
}

/**
 * status_handle -
 */
void	status_handle(void)
{
	int	exit_status;

	if (WIFEXITED(g_global.status))
	{
		exit_status = WEXITSTATUS(g_global.status);
		g_global.status = exit_status;
	}
	else
	{
		if (g_global.child_signal == 1)
			g_global.status = 130;
		else if (g_global.child_signal == 2)
			g_global.status = 131;
	}
}
