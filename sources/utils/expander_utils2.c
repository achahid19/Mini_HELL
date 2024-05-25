/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:13:15 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/24 18:36:46 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool	string_handler(token_ptr *tokens_list);
t_bool	check_if_dollar(char c, token_ptr *tokens_list);
int		get_biggest_len(char *envp, char *dollar_tk);
void	tokens_expander_helper(token_ptr tokens_list, char **envp,
			t_expand d);

/**
 * string_hanlder - handle the execution of the
 * expansion of dollar sign, in double quoted string
*/
t_bool	string_handler(token_ptr *tokens_list)
{
	if ((*tokens_list)->token_type == doublequote_token)
	{
		*tokens_list = (*tokens_list)->next;
		if ((*tokens_list) == NULL
			|| (*tokens_list)->token_type == doublequote_token)
			return (false);
	}
	return (true);
}

/**
 * check_if_dollar -
*/
t_bool	check_if_dollar(char c, token_ptr *tokens_list)
{
	if (c == '\0')
	{
		(*tokens_list) = (*tokens_list)->next;
		return (false);
	}
	// its a dollar $.
	return (true);
}

/**
 * get_biggest_len -
*/
int		get_biggest_len(char *envp, char *dollar_tk)
{
	int	envp_len;
	int dollar_tk_len;

	envp_len = 	get_variable_len(envp);
	dollar_tk_len = ft_strlen(dollar_tk);
	if (envp_len > dollar_tk_len)
		return (envp_len);
	return (dollar_tk_len);
}

int	dollars_count(char *token)
{
	int	dollars = 0;

	while (*token)
	{
		if (*token == '$')
			dollars++;
		token++;
	}
	return (dollars);
}
/**
 * tokens_expander_helper -
*/
void	tokens_expander_helper(token_ptr tokens_list, char **envp,
			t_expand d)
{
	while (tokens_list != NULL)
	{
		d.dollars_count = dollars_count(tokens_list->token);
		while (d.dollars_count-- > 0)
		{
			if (check_type(tokens_list->token_type) == true)
			{
				if (string_handler(&tokens_list) == false)
					return ;
				d.ptr_token = find_dollar(tokens_list->token);
				printf("next dollar found: %s\n", d.ptr_token);
				if (check_if_dollar(*d.ptr_token, &tokens_list) == false)
					continue ;
				while (check_expander_chars(d.ptr_token[d.dollar_tk_len + 1])
						== true)
					d.dollar_tk_len++;
				printf("dollar len: %d in %d\n", d.dollar_tk_len, d.dollars_count);
				if (d.dollar_tk_len == 0) // if we have only dollar token
					break;
				d.tmp_dollar_len = d.dollar_tk_len;
				d.dollar_tk = extract_dollar_token(d.ptr_token, d.dollar_tk,
								d.dollar_tk_len);
				d.dollar_tk = get_value(d.dollar_tk, &d.dollar_tk_len, envp);
				// free tokens_list before pointig to new memory address
				tokens_list->token = expanding(d.dollar_tk, tokens_list->token,
										d.tmp_dollar_len);
				tokens_list->token_length = ft_strlen(tokens_list->token);
				printf("token now is: %s\n", tokens_list->token);
				d.ptr_token = NULL;
				d.dollar_tk_len = 0;
			}
		}
		tokens_list = tokens_list->next;
	}
}
