/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 06:22:16 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/28 06:22:20 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool			extract_cmd_helper(token_ptr *tokens_list,
					int *i, char **full_cmd);
static t_bool	whitespace_checker(token_ptr *tokens_list,
					int *i, char **full_cmd);
t_bool			get_infos_helper(token_ptr *tokens_list,
					t_bool *flag, int *rows);

/**
 * extract_cmd_helper -
*/
t_bool	extract_cmd_helper(token_ptr *tokens_list,
			int *i, char **full_cmd)
{
	if ((*tokens_list)->token_type == pipe_token)
	{
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list)->token_type == whitespace_token)
			(*tokens_list) = (*tokens_list)->next;
	}
	while ((*tokens_list)->token_type != whitespace_token
		&& (*tokens_list)->token_type != pipe_token)
	{
		if ((*tokens_list)->token_type == cmd
			|| (*tokens_list)->token_type == string_token
			|| (*tokens_list)->token_type == word_token)
			full_cmd[*i] = ft_strjoin(full_cmd[*i], (*tokens_list)->token);
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) == NULL)
		{
			*i += 1;
			full_cmd[*i] = NULL;
			return (false);
		}
	}
	if (whitespace_checker(tokens_list, i, full_cmd) == false)
		return (false);
	return (true);
}

/**
 * whitespace_checker -
*/
static t_bool	whitespace_checker(token_ptr *tokens_list,
					int *i, char **full_cmd)
{
	while ((*tokens_list)->token_type == whitespace_token)
	{
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) == NULL)
		{
			*i += 1;
			full_cmd[*i] = NULL;
			return (false);
		}
	}
	return (true);
}

t_bool	get_infos_helper(token_ptr *tokens_list,
			t_bool *flag, int *rows)
{
	if ((*tokens_list)->token_type == pipe_token)
		(*tokens_list) = (*tokens_list)->next;
	while ((*tokens_list)->token_type != whitespace_token
		&& (*tokens_list)->token_type != pipe_token)
	{
		if (((*tokens_list)->token_type == cmd
				|| (*tokens_list)->token_type == string_token
				|| (*tokens_list)->token_type == word_token)
			&& *flag == true)
		{
			*flag = false;
			*rows += 1;
		}
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) == NULL)
			return (false);
	}
	return (true);
}
