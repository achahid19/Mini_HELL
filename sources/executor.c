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

void	exec_command(token_ptr tokens_list, char **envp, char *user_input);
char	**extract_command(token_ptr tokens_list);
int		get_infos(token_ptr tokens_list);
void	ft_pipe(char **av, char **envp, token_ptr tokens_list,
			char *user_input);

/**
 * executor -
*/
void	executor(token_ptr tokens_list, char **envp, char *user_input)
{
	int	pipes;

	pipes = check_pipes_num(tokens_list);
	while (pipes--)
	{
		exec_command(tokens_list, envp, user_input);
		tokens_list = get_next_pipe(tokens_list);
	}
	wait(NULL);
}

/**
 * exec_command -
*/
void	exec_command(token_ptr tokens_list, char **envp, char *user_input)
{
	char	**full_cmd;

	/* // extract till Pipe or NULL. and return 2d array */
	full_cmd = extract_command(tokens_list); // TODO later: check for built_ins
	for (int z = 0; full_cmd[z] != NULL; z++)
		printf("--->%s\n", full_cmd[z]);
	ft_pipe(full_cmd, envp, tokens_list, user_input);
	free_cmd_table(full_cmd);
	// handle red, and appends on linked_list.
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

char	*ft_get_path(char **envp)
{
	size_t	count;

	count = 0;
	while (ft_strncmp(envp[count], "PATH", 4) != 0)
	{
		/* if (ft_strncmp(envp[count], "PATH", 4) == -1)
			return (NULL); */
		count++;
	}
	return (envp[count]);
}

char	*ft_cmd_path(char *cmd_path)
{
	int		count;
	char	*cmd;
	int		index;

	count = 0;
	while (cmd_path[count] != ' ' && cmd_path[count])
		count++;
	cmd = (char *)malloc(sizeof(char) * count + 1);
	if (cmd == NULL)
		return (NULL);
	index = 0;
	while (index < count)
	{
		cmd[index] = cmd_path[index];
		index++;
	}
	cmd[index] = '\0';
	return (cmd);
}

char	*ft_find_cmd(char *cmd, char **envp)
{
	t_var	obj;

	obj.path_to_cmd = NULL;
	obj.i = 0;
	obj.env = ft_get_path(envp);
	if (obj.env == NULL)
		return (NULL);
	obj.token = &cmd;
	obj.path = ft_split(obj.env, ':');
	while (obj.path[obj.i] != NULL)
	{
		obj.path[obj.i] = ft_strjoin(obj.path[obj.i], "/");
		obj.i++;
	}
	obj.i = 0;
	while (obj.path[obj.i] != NULL)
	{
		obj.path[obj.i] = ft_strjoin(obj.path[obj.i], obj.token[0]);
		if (access(obj.path[obj.i], X_OK) == 0)
		{
			obj.path_to_cmd = ft_strdup(obj.path[obj.i]);
			if (obj.path_to_cmd == NULL)
			{
				free_cmd_table(obj.path);
				return (NULL);
			}
			break ;
		}
		obj.i++;
	}
	free_cmd_table(obj.path);
	return (obj.path_to_cmd);
}

void	dup_and_close(int *end, int i)
{
	if (i == 1)
	{
		dup2(end[i], STDOUT_FILENO);
		close(end[0]);
		close(end[1]);
	}
	else if (i == 0)
	{
		dup2(end[i], STDIN_FILENO);
		close(end[0]);
		close(end[1]);
	}
}

void	ft_pipe(char **av, char **envp, token_ptr tokens_list,
			char *user_input)
{
	pid_t	child_pid;
	int		end[2];
	char	*path_to_cmd;

	if (*av == NULL)
		return ;
	/* for (int z = 0; av[z] != NULL; z++)
		printf("--->%s\n", av[z]); */
	if (pipe(end) == -1)
		exit(-1);
		/* ft_error_exit(); */
	child_pid = fork();
	if (child_pid == 0)
	{
		/* dup_and_close(end, 1); */
		if (ft_strncmp(av[0], "/", 1) == 0)
		{
			path_to_cmd = ft_cmd_path(av[0]);
			if (access(path_to_cmd, X_OK) == 0)
				execve(path_to_cmd, av, envp);
			else
			{
				free_all(tokens_list, user_input);
				free_cmd_table(av);
				free(path_to_cmd);
				print_error("No such file or directory !");
				exit (-1);
			}
				/* free_and_exit("\033[1;31mPath Not Found!\033[0m", path_to_cmd); */
		}
		path_to_cmd = ft_find_cmd(av[0], envp);
		/* if (path_to_cmd == NULL)
			ft_error_print("\033[1;33mError: Cmd not found!\033[0m"); */
		if (path_to_cmd == NULL)
			path_to_cmd = av[0];
		if (execve(path_to_cmd, av, envp) == -1)
		{
			//perror("execve");
			 //fprintf(stderr, "%s: %s\n", "/bin/lsdjfk", strerror(errno));
			print_error("command not found !");
			//free(path_to_cmd);
			free_cmd_table(av);
			/* printf("exited\n"); */
			free_all(tokens_list, user_input);
			exit(-1);
		}
			/* ft_error_exit(); */
	}
	/* dup_and_close(end, 0); */
}
