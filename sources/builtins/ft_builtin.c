/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:10:38 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/16 18:44:02 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int		nb_args(char **args)
{
	int		len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

t_bool		ft_echo(char **av)
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	if (nb_args(av) > 1)
	{
		while (av[i] && ft_strncmp(av[i], "-n", 2) == 0)
		{
			option = 1;
			i++;
		}
		while (av[i])
		{
			ft_putstr_fd(av[i], 1);
			if (av[i + 1] && av[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option == 0)
		write(1, "\n", 1);
	return (true);
}

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

t_bool		ft_env(t_var *data ,char **av)
{
	t_env	*tmp;

	tmp = data->e;
	if (nb_args(av) > 1)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (false);
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(tmp->value, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (true);
}

t_bool		exec_builtin(char **av, t_var *data)
{
    if (ft_strncmp(av[0], "echo",4) == 0)
        return (ft_echo(av));
    else if (ft_strncmp(av[0], "pwd",3) == 0)
        return (ft_pwd(av));
    else if (ft_strncmp(av[0], "env",3) == 0)
        return (ft_env(data,av));
    // else if (ft_strncmp(av[0], "cd", 2) == 0)
    //     return (ft_cd(av));
    // else if (ft_strcmp(av[0], "export") == 0)
    //     return (ft_export(av, data));
    // else if (ft_strcmp(av[0], "unset") == 0)
    //     return (ft_unset(av, data));
    // else if (ft_strcmp(av[0], "exit") == 0)
    //     return (ft_exit(av, data));
	return (false);
}