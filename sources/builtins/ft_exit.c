/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:01:15 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/24 01:53:26 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int	nb_count(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit_helper(char **av, t_var data)
{
	write(2, "exit\n", 5);
	write(2, "exit: numeric argument required\n", 33);
	g_global.status = 2;
	free_close_child(&data, av);
	exit(g_global.status);
}

void	ft_exit_helper2(t_var *data, char **av)
{
	int	i;

	write(2, "exit\n", 5);
	i = ft_atoi(av[1]);
	if (ft_strlen(av[1]) > 19)
	{
		ft_putstr_fd("exit numeric argument required", 2);
		i = 2;
	}
	free_close_child(data, av);
	exit((unsigned char)i);
}

t_bool	ft_exit(char **av, t_var data)
{
	if (nb_count(av) == 1)
	{
		write(2, "exit\n", 5);
		free_close_child(&data, av);
		exit(g_global.status);
	}
	if (ft_isnumber(av[1]) == false)
		ft_exit_helper(av, data);
	else if (nb_count(av) > 2 && ft_isnumber(av[1]) == true)
	{
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
		g_global.status = 1;
		return (false);
	}
	else
		ft_exit_helper2(&data, av);
	return (true);
}
