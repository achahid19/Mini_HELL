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

void	exec_command(token_ptr tokens_list, t_var data);
char	**extract_command(token_ptr tokens_list);
int		get_infos(token_ptr tokens_list);
void	ft_pipe(char **av, t_var data, t_bool pipe_switcher);

/**
 * executor -
*/
void	executor(token_ptr tokens_list, char **envp, char *user_input)
{
	t_var	data;

	data.tokens_list = tokens_list;
	data.envp = envp;
	data.user_input = user_input;
	data.pipes = check_pipes_num(tokens_list);
	data.std_in = dup(STDIN);
	while (data.pipes)
	{
		exec_command(tokens_list, data);
		tokens_list = get_next_pipe(tokens_list);
		data.pipes--;
	}
	dup2(data.std_in, STDIN);
	close(data.std_in);
	while (wait(NULL) > 0)
		;
}

/**
 * exec_command -
*/
void	exec_command(token_ptr tokens_list, t_var data)
{
	char	**full_cmd;

	// handle red, and appends on linked_list.
	full_cmd = extract_command(tokens_list); // TODO later: check for built_ins
	/* for (int z = 0; full_cmd[z] != NULL; z++)
		printf("--->%s\n", full_cmd[z]); */
	if (data.pipes > 1)
		ft_pipe(full_cmd, data, true);
	else if (data.pipes == 1)
		ft_pipe(full_cmd, data, false);
	free_cmd_table(full_cmd);
	
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
	full_cmd = (char **)malloc(sizeof(char *) * (rows + 1));
	i = 0;
	while (i < rows)
	{	
		full_cmd[i] = NULL;
		if (tokens_list->token_type != string_token
			&& tokens_list->token_type != cmd
			&& tokens_list->token_type != word_token)
		{
			tokens_list = tokens_list->next;
			continue;
		}
		if (extract_cmd_helper(&tokens_list, &i, full_cmd) == false)
			return (full_cmd);
		i++;
	}
	full_cmd[i] = NULL;
	return (full_cmd);
}

/**
 * get_infos - will is not space treath all the cmd + words + string as one token 
 * to be merged later on. [1 token = 1 row].
*/
int	get_infos(token_ptr tokens_list)
{
	int		rows;
	t_bool	flag;

	rows = 0;
	flag = true;
	while (tokens_list)
	{
		if (get_infos_helper(&tokens_list, &flag, &rows) == false)
			return (rows);
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

/**
 * ft_pipe -
*/
void	ft_pipe(char **av, t_var data, t_bool pipe_switcher)
{
	if (*av == NULL)
		return ;
	if (pipe(data.end) == -1)
		exit(EXIT_FAILURE);
	data.child_pid = fork();
	if (data.child_pid == 0)
		child_exec_cmd(av, data, pipe_switcher);
	if (pipe_switcher == true)
		dup_and_close(data.end, STDIN);
}
