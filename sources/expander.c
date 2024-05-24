/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:40:19 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/22 09:40:21 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

// add expanding for doublequotes (DONE)
// reduce tokens_expander function for norminette (in progress)
// fix urgent problem: $PWDa, only envp lenght is compared!
	// handle each one $PWD$PWD (SegFault)
// Case to handle: $$ and $?
// handle leaks
// DO protect if envp is NULL

void	tokens_expander(token_ptr tokens_list, char **envp);
char	*extract_dollar_token(char *ptr_token, char *dollar_tk,
			int dollar_tk_len);
char	*get_value(char *dollar_tk, int *dtk_len, char **envp);
char	*expanding(char *dollar_tk, char *token, int tmp_tk_len);
void	move_data(t_expand *data, char *dollar_tk, char *token);

/**
 * tokens_expander -
*/
void	tokens_expander(token_ptr tokens_list, char **envp)
{
	t_expand	d;

	d.dollar_tk_len = 0;
	d.tmp_dollar_len = 0;
	d.ptr_token = NULL;
	d.new_token = NULL;
	tokens_expander_helper(tokens_list, envp, d);
}

/**
 * extract_dollar_token -
*/
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
 * get_value -
*/
char	*get_value(char *dollar_tk, int *dtk_len, char **envp)
{
	// check dollar_tk with envp[i] until we hit '=', which means
	// check variable's names.
	size_t	i;
	int		len;
	char	*new_token;
	int		cmp_len;

	i = 0;
	while (envp[i] != NULL)
	{
		cmp_len = get_variable_len(envp[i]);
		if (ft_strncmp(dollar_tk, envp[i], cmp_len) == 0)
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
 * expanding -
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

/**
 * move-data -
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
