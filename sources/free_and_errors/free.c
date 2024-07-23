/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:31:44 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/23 21:17:19 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

/**
 * free_tokens -
*/
void	error(const char *cmd, const char *msg)
{
	g_global.status = 1;
	if (msg)
		printf("%s: %s\n", cmd, msg);
	else
		perror(cmd);
}

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

/**
 * free_env_list
*/
void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next_node;
	}
}

/**
 * free_global_env
*/
void	free_global_env(void)
{
	free_env_list(g_global.e);
	g_global.e = NULL;
}

/**
 * free_all -
*/
void	free_all(token_ptr tokens_list, char *user_input,
			char **av)
{
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

