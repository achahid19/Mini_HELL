/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 08:59:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/13 08:59:48 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	quotes_substitut(char **cmd_table);
void	close_fds(t_var *data);
t_bool	export_check(char **av, t_var data, t_bool pipe_switcher);
char	**transform_env(void);
void	join_key_value(char *str, char **envp, int i,
			t_env *tmp);

/**
 * quotes_substitut -
*/
void	quotes_substitut(char **cmd_table)
{
	size_t	i;

	if (!cmd_table || !*cmd_table)
		return ;
	i = 1;
	while (cmd_table[i])
	{
		if (ft_strncmp(cmd_table[i], "\"\"", ft_strlen(cmd_table[i])) == 0
			|| ft_strncmp(cmd_table[i], "''", ft_strlen(cmd_table[i])) == 0)
		{
			free(cmd_table[i]);
			cmd_table[i] = malloc(1);
			cmd_table[i][0] = '\0';
		}
		i++;
	}
}

/**
 * close_fds -
*/
void	close_fds(t_var *data)
{
	if (data->fd[0] != false)
		close(data->fd[0]);
	if (data->fd[1] != false)
		close(data->fd[1]);
	if (data->end[0] != false)
		close(data->end[0]);
	if (data->end[1] != false)
		close(data->end[1]);
}

/**
 * export_check -
 */
t_bool	builtin_check(char **av, t_var data, t_bool pipe_switcher)
{
	if (av == NULL)
		return (false);
	if (export_check(av, data, pipe_switcher) == true)
		return (true);
	else if (unset_check(av, data, pipe_switcher) == true)
		return (true);
	else if (exit_check(av, data, pipe_switcher) == true)
		return (true);
	else if (cd_check(av, data, pipe_switcher) == true)
		return (true);
	return (false);
}

/**
 * transform_env -
 */
char	**transform_env(void)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*str;

	i = 0;
	tmp = g_global.e;
	envp = NULL;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = g_global.e;
	str = NULL;
	while (tmp)
	{
		join_key_value(str, envp, i, tmp);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * join_key_value -
 */
void	join_key_value(char *str, char **envp, int i,
			t_env *tmp)
{
	if (str != NULL)
		free(str);
	str = ft_strdup(tmp->key);
	envp[i] = ft_strjoin(str, "=");
	envp[i] = ft_strjoin(envp[i], tmp->value);
}
