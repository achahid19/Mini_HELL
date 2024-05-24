/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:16:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/24 18:37:01 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

char	*find_dollar(char *ptr_token);
t_bool	check_expander_chars(char c);
int		get_variable_len(char *envp);
char	*retrieve_value(char *envp, char *dollar_tk);
t_bool	check_type(int token_type);

/**
 * find_dollar -
*/
char	*find_dollar(char *ptr_token)
{
	while (*ptr_token)
	{
		if (*ptr_token == '$')
			break;
		ptr_token++;
	}
	return (ptr_token);
}

/**
 * check_expander_chars -
*/
t_bool	check_expander_chars(char c)
{
	if (ft_isalpha(c))
		return (true);
	else if (ft_isdigit(c))
		return (true);
	else if (c == '_')
		return (true);
	return (false);
}

/**
 * get_variable_len -
*/
int	get_variable_len(char *envp)
{
	int		len_variable;

	len_variable = 0;
	while (*envp != '=')
	{
		envp++;
		len_variable++;
	}
	return (len_variable);
}

/**
 * retrieve_value -
*/
char	*retrieve_value(char *envp, char *dollar_tk)
{
	int	value_len;
	int i = 0;

	value_len = 0;
	while (*envp != '=' && *envp)
		envp++;
	envp++; // after '='
	while (envp[value_len])
		value_len++;
	printf("envp pointer: %s and len: %d\n", envp, value_len);
	dollar_tk = ft_realloc(dollar_tk, value_len); // TO do free dollar token.
	while (envp[i])
	{
		dollar_tk[i] = envp[i];
		i++;
	}
	dollar_tk[value_len] = '\0';
	return (dollar_tk);
}

/**
 * check_type -
*/
t_bool	check_type(int token_type)
{
	return (token_type == word_token
			|| token_type == doublequote_token);
}
