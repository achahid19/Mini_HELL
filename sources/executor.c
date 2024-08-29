/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:57 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/24 01:26:53 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"
#include "../includes/global.h"

void	executor(t_ptr tokens_list, char **envp, char *user_input);
void	exec_command(t_ptr tokens_list, t_var data);
char	**extract_command(t_ptr tokens_list);
int		get_infos(t_ptr tokens_list);
void	ft_pipe(char **av, t_var data, t_bool pipe_switcher);

/**
 * executor -
*/
void	executor(t_ptr tokens_list, char **envp, char *user_input)
{
	t_var	data;

	data.tokens_list = tokens_list;
	data.user_input = user_input;
	data.pipes = check_pipes_num(tokens_list);
	data.std_in = dup(STDIN);
	data.fd[0] = 0;
	data.fd[1] = 0;
	data.envp = transform_env();
	data.e = envp;
	while (data.pipes)
	{
		dollar_status_check(tokens_list);
		exec_command(tokens_list, data);
		tokens_list = get_next_pipe(tokens_list);
		data.pipes--;
	}
	free_cmd_table(data.envp);
	dup2(data.std_in, STDIN);
	close(data.std_in);
	while (wait(&g_global.status) > 0)
		status_handle();
}

/**
 * exec_command -
*/
void	exec_command(t_ptr tokens_list, t_var data)
{
	char	**full_cmd;

	if (space_trim(tokens_list) == true)
		return ;
	full_cmd = extract_command(tokens_list);
	quotes_substitut(full_cmd);
	if (data.pipes > 1)
		ft_pipe(full_cmd, data, true);
	else if (data.pipes == 1)
		ft_pipe(full_cmd, data, false);
	if (full_cmd)
		free_cmd_table(full_cmd);
}

/**
 * extract_command -
*/
char	**extract_command(t_ptr tokens_list)
{
	char	**full_cmd;
	int		rows;
	int		i;

	rows = get_infos(tokens_list);
	if (rows == 0)
		return (NULL);
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
			continue ;
		}
		if (extract_cmd_helper(&tokens_list, &i, full_cmd) == false)
			return (full_cmd);
		i++;
	}
	full_cmd[i] = NULL;
	return (full_cmd);
}

/**
 * get_infos - will is not space treath all
 * the cmd + words + string as one token 
 * to be merged later on. [1 token = 1 row].
*/
int	get_infos(t_ptr tokens_list)
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
	signal(SIGINT, handler_2);
	signal(SIGQUIT, handler_3);
	if (input_red_stream(&data) == false)
		return ;
	if (av)
		ft_underscore(av[0]);
	if (pipe(data.end) == -1)
		exit(EXIT_FAILURE);
	if (builtin_check(av, data, pipe_switcher) == true)
		return ;
	data.child_pid = fork();
	if (data.child_pid == 0)
		child_exec_cmd(av, &data, pipe_switcher);
	if (pipe_switcher == true)
		dup_and_close(data.end, STDIN);
	close_fds(&data);
}
