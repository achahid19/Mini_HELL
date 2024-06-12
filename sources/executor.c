/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:57 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/05 10:30:58 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

// cmd (could be seperated [needs to be joined] "" && '')+ args (words + strings)
// + heredoc (2 tokens) + appends (2 tokens) + redirections (2 tokens)
// note that all 2 tokens are next to each other.

// current data structure is linked list, -> execve needs a table of strings
// table of strings containing the cmd as av[0] then all args av[n].

// So first needs to transform the linked list into 2d array, but not all
// the linked list once!!!!!!!!!!!!
// transform the command needed on each process :) hmmmm so get_next_pipe will
// do his jooob yeeaaaaah!!!

// special chars without the second one means -> >> '' (since sytax is good).
// not working for args -> because we could have only cmd without args.

void	exec_command(token_ptr tokens_list);
char	**extract_command(token_ptr tokens_list);
int		get_infos(token_ptr tokens_list);

/**
 * executor -
*/
void	executor(token_ptr tokens_list)
{
	int	pipes;

	pipes = check_pipes_num(tokens_list);
	while(pipes--)
	{
		exec_command(tokens_list);
		tokens_list = get_next_pipe(tokens_list);
	}
	/* wait(NULL); */
}

/**
 * exec_command -
*/
void	exec_command(token_ptr tokens_list)
{
	char	**full_cmd;
	// first thing I need to extract the full command in a 2d array
		// cmd + args (words + strings).
	/* // extract till Pipe or NULL. and return 2d array */
	full_cmd = extract_command(tokens_list); // TODO later: check for built_ins
	for (int z = 0; full_cmd[z] != NULL; z++)
		printf("--->%s\n", full_cmd[z]);
	// handle red, heredocs and appends on linked_list.
}

/**
 * extract_command -
*/
char	**extract_command(token_ptr tokens_list)
{
	char	**full_cmd;
	int		rows;
	int		i;

	rows = get_infos(tokens_list);
	printf("rows: %d\n", rows);
	full_cmd = (char **)malloc(sizeof(char *) * (rows + 1)); // needs how many rows;
	// so needs 2 infos, number of cmd_n and rows(cmd + args).
	i = 0;
	while (i < rows)
	{	
		full_cmd[i] = NULL;
		if (tokens_list->token_type != string_token && tokens_list->token_type != cmd
			&& tokens_list->token_type != word_token)
		{
			tokens_list = tokens_list->next;
			continue;
		}
		if (tokens_list->token_type == pipe_token)
		{
			tokens_list = tokens_list->next;
			if (tokens_list->token_type == whitespace_token)
				tokens_list = tokens_list->next;
		}
		while (tokens_list->token_type != whitespace_token &&
				tokens_list->token_type != pipe_token)
		{
			if (tokens_list->token_type == cmd ||
			tokens_list->token_type == string_token ||
			tokens_list->token_type == word_token)
				full_cmd[i] = ft_strjoin(full_cmd[i], tokens_list->token);
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
			{
				i++;
				full_cmd[i] = NULL;
				return (full_cmd) ;
			}
		}
		while (tokens_list->token_type == whitespace_token)
		{
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
			{
				i++;
				full_cmd[i] = NULL;
				return (full_cmd) ;
			}
		}
		i++;
	}
	full_cmd[i] = NULL;
	return (full_cmd);
}

/**
 * get_infos -
*/
int	get_infos(token_ptr tokens_list)
{
	// for the rows, no whitespace -> join cmd + words + strings.
	int		rows;
	t_bool	flag;

	rows = 0;
	flag = true;
	while (tokens_list)
	{
		// will is not space treath all the cmd + words + string as one token
		// to be merged later on. [1 token = 1 row].
		if (tokens_list->token_type == pipe_token)
			tokens_list = tokens_list->next;
		while (tokens_list->token_type != whitespace_token &&
				tokens_list->token_type != pipe_token)
		{
			if ((tokens_list->token_type == cmd ||
			tokens_list->token_type == string_token ||
			tokens_list->token_type == word_token) && flag == true)
			{
				flag = false;
				rows++;
			}
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
				return (rows);
		}
		while (tokens_list->token_type == whitespace_token)
		{
			tokens_list = tokens_list->next;
			if (tokens_list == NULL)
				return (rows);
		}
		if (tokens_list->token_type == pipe_token)
			return (rows);
		flag = true;
	}
	return (rows);
}
