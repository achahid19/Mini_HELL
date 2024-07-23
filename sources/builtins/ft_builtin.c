/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:10:38 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 18:16:31 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"


t_bool 		ft_pwd(char **av)
{
	char	*pwd;

	if (nb_args(av) > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (false);
	}
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
	return (true);
}

t_bool		exec_builtin(char **av)
{
	if (ft_strncmp(av[0], "echo",4) == 0)
	{
		return (ft_echo(av));
	}
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
	{
		return (ft_pwd(av));
	}
	else if (ft_strncmp(av[0], "env", 3) == 0)
	{
		return (ft_env(av));
	}
	else if (ft_strncmp(av[0], "export", 6) == 0)
	{
		return (ft_export(av));
	}

	return (false);
}
