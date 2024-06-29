/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:18:28 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/29 13:18:29 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	child_exec_cmd(char **av, t_var data, t_bool pipe_switcher);
void	dup_and_close(int *end, int i);
char	*ft_cmd_path(char *cmd_path);
char	*ft_get_path(char **envp);
char	*ft_find_cmd(char *cmd, char **envp);

/**
 * child_exec_cmd -
*/
void	child_exec_cmd(char **av, t_var data, t_bool pipe_switcher)
{
	if (pipe_switcher == true)
			dup_and_close(data.end, STDOUT);
		if (ft_strncmp(av[0], "/", 1) == 0)
		{
			data.path_to_cmd = ft_cmd_path(av[0]);
			if (access(data.path_to_cmd, X_OK) == 0)
				execve(data.path_to_cmd, av, data.envp);
			else
			{
				free_all(data.tokens_list, data.user_input);
				free_cmd_table(av);
				free(data.path_to_cmd);
				print_error("kssh: No such file or directory !\n");
				exit(-1);
			}
		}
		data.path_to_cmd = ft_find_cmd(av[0], data.envp);
		if (data.path_to_cmd == NULL)
			data.path_to_cmd = av[0];
		if (execve(data.path_to_cmd, av, data.envp) == -1)
		{
			print_error("kssh: command not found !\n");
			free_cmd_table(av);
			free_all(data.tokens_list, data.user_input);
			exit(-1);
		}
}

/**
 * dup_and_close -
*/
void	dup_and_close(int *end, int i)
{
	if (i == STDOUT)
	{
		dup2(end[i], STDOUT_FILENO);
		close(end[0]);
		close(end[1]);
	}
	else if (i == STDIN)
	{
		dup2(end[i], STDIN_FILENO);
		close(end[0]);
		close(end[1]);
	}
}

/**
 * ft_cmd_path -
*/
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

/**
 * ft_get_path -
*/
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

/**
 * ft_find_cmd -
*/
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
