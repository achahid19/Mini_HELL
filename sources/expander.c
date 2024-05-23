/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:40:19 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/22 09:40:21 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

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

char *extract_dollar_token(char *ptr_token, char *dollar_tk, int dollar_tk_len)
{
	int i;

	i = 0;
	dollar_tk = (char *)malloc(sizeof(char) * dollar_tk_len + 1); // need to be freed when done
	while (i < dollar_tk_len)
	{
		dollar_tk[i] = ptr_token[i + 1];
		i++;
	}
	dollar_tk[i] = '\0';
	return (dollar_tk);
}

/**
 * 
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
 * 
*/
char	*get_value(char *dollar_tk, int *dtk_len, char **envp)
{
	// check dollar_tk with envp[i] until we hit '=', which means
	// check variable's names.
	size_t	i;
	int		len;
	char	*new_token;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(dollar_tk, envp[i], *dtk_len) == 0)
		{
			// must return the new one
			// must retrive a pointer after '=' sign
			dollar_tk = retrieve_value(envp[i], dollar_tk);
			*dtk_len = ft_strlen(dollar_tk);
			return (dollar_tk);
		}
		i++;
	}
	// not find.
	free(dollar_tk);
	dollar_tk = malloc(1);
	dollar_tk[0] = '\0';
	return (dollar_tk);
}

/**
 * move_data -
*/
void	move_data(t_expand *data, char *dollar_tk, char *token)
{
	data->i = 0;
	while (data->i < data->new_tk_len)
	{
		if (*token != '$')
		{
			data->new_token[data->i] = *token;
			token++;
			data->i++;
		}
		else if (*token == '$')
		{
			printf("sdkfjs %d\n", data->tmp_tk_len);
			while (data->tmp_tk_len-- >= 0)
				token++;
			printf("pointing at %s\n", token);
			while (data->dollar_tk_len--)
			{
				data->new_token[data->i] = *dollar_tk;
				dollar_tk++;
				data->i++;
			}
		}
	}
	data->new_token[data->i] = '\0';
}

/**
 * expansion -
*/
char	*expanding(char *dollar_tk, char *token, int tmp_tk_len)
{
	// aa$PWD-- (token)
	// /bin/ls for instance (dollar_tk)
	t_expand	data;

	data.new_tk_len = 0;
	data.i = 0;
	data.dollar_tk_len = ft_strlen(dollar_tk); // retrieved value
	data.tmp_tk_len = tmp_tk_len;
	while (token[data.i])
	{
		if (token[data.i] == '$')
		{
			while (tmp_tk_len-- >= 0)
				data.i++;
		}
		if (token[data.i] == '\0')
			break;
		data.new_tk_len++;
		data.i++;
	}
	data.new_tk_len += data.dollar_tk_len;
	data.new_token = malloc(sizeof(char) * data.new_tk_len  + 1);
	move_data(&data, dollar_tk, token);
	// free what is needed to be freed
	return (data.new_token);
}

void	tokens_expander(token_ptr tokens_list, char **envp)
{
	char	*ptr_token;
	int		dollar_tk_len;
	char	*dollar_tk;
	int		tmp_dollar_len;

	dollar_tk_len = 0;
	tmp_dollar_len = 0;
	// prevent from envp is NULL // TO DO
	while (tokens_list != NULL)
	{
		if (tokens_list->token_type == word_token)
		{
			ptr_token = tokens_list->token;
			ptr_token = find_dollar(ptr_token);
			if (*ptr_token == '\0')
			{
				tokens_list = tokens_list->next;
				continue ;
			}
			while (check_expander_chars(ptr_token[dollar_tk_len + 1]) == true)
				dollar_tk_len++;
			if (dollar_tk_len == 0) // if we have only dollar token
				break;
			tmp_dollar_len = dollar_tk_len;
			dollar_tk = extract_dollar_token(ptr_token, dollar_tk, dollar_tk_len);
			dollar_tk = get_value(dollar_tk, &dollar_tk_len, envp);
			tokens_list->token = expanding(dollar_tk, tokens_list->token, tmp_dollar_len);
			tokens_list->token_length = ft_strlen(tokens_list->token);
			// dont forget free token on the list and dollar_tk;
			// dollar_tk points to expanded token + length dereferecend
			// after expanding, concatenate the expanded token to its place
			printf("---> dollar_tk: %s\n", dollar_tk);
		}
		tokens_list = tokens_list->next;
	}
}
