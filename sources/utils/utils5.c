/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:10:24 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/24 00:14:19 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int		big_len(char *str1, char *str2);
t_bool	export_check(char **av, t_var data, t_bool pipe_switcher);
t_bool	unset_check(char **av, t_var data, t_bool pipe_switcher);
t_bool	exit_check(char **av, t_var data, t_bool pipe_switcher);
t_bool	cd_check(char **av, t_var data, t_bool pipe_switcher);

/**
 * big_len -
 */
int	big_len(char *str1, char *str2)
{
	int	len;

	if (ft_strlen(str1) > ft_strlen(str2))
		len = ft_strlen(str1);
	else
		len = ft_strlen(str2);
	return (len);
}

/**
 * export_check -
 */
t_bool	export_check(char **av, t_var data, t_bool pipe_switcher)
{
	int	len;

	len = big_len(av[0], "export");
	if (ft_strncmp(av[0], "export", len) == 0 && av[1] != NULL)
	{
		if (ft_export(av) == false)
			g_global.status = 1;
		if (pipe_switcher == true)
			dup_and_close(data.end, STDIN);
		close_fds(&data);
		return (true);
	}
	return (false);
}

/**
 * unset_check -
 */
t_bool	unset_check(char **av, t_var data, t_bool pipe_switcher)
{
	int	len;

	len = big_len(av[0], "unset");
	if (ft_strncmp(av[0], "unset", len) == 0)
	{
		ft_unset(av);
		if (pipe_switcher == true)
			dup_and_close(data.end, STDIN);
		close_fds(&data);
		return (true);
	}
	return (false);
}

/**
 * exit_check -
 */
t_bool	exit_check(char **av, t_var data, t_bool pipe_switcher)
{
	int	len;

	len = big_len(av[0], "exit");
	if (ft_strncmp(av[0], "exit", len) == 0)
	{
		if (pipe_switcher == true)
			return (false);
		if (ft_exit(av, data) == false)
			return (true);
	}
	return (false);
}

/**
 * cd_check -
 */
t_bool	cd_check(char **av, t_var data, t_bool pipe_switcher)
{
	int	len;

	len = big_len(av[0], "cd");
	if (ft_strncmp(av[0], "cd", len) == 0)
	{
		ft_cd(av);
		if (pipe_switcher == true)
			dup_and_close(data.end, STDIN);
		close_fds(&data);
		return (true);
	}
	return (false);
}
