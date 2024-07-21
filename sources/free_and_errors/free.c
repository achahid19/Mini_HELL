/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:31:44 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/21 19:15:21 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	free_tokens(token_ptr tokens_list)
{
	token_ptr	tmp;

	while (tokens_list)
	{
		tmp = tokens_list;
		free(tokens_list->token);
		tokens_list = tokens_list->next;
		free(tmp);
	}
}

void free_env_list(t_env *head) {
    t_env *current = head;
    t_env *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next_node;
    }
}

void free_global_env()
{
    free_env_list(g_global.e);
    g_global.e = NULL;
}


void	free_all(token_ptr tokens_list, char *user_input,
			char **av)
{
	/* if (g_global.e != NULL)
		free_global_env(); */
	if (tokens_list != NULL)
		free_tokens(tokens_list);
	if (user_input != NULL)
		free(user_input);
	if (av != NULL)
		free_cmd_table(av);
}

/**
 * free_cmd_table -
*/
void	free_cmd_table(char **full_cmd)
{
	size_t	i;

	i = 0;
	while (full_cmd[i] != NULL)
	{
		free(full_cmd[i]);
		i++;
	}
	free(full_cmd);
}
