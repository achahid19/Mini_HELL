/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:46:59 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 04:47:51 by akajjou          ###   ########.fr       */
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

void	ft_putstr_echo(char *s, int fd)
{
	size_t	count;

	if (!s || fd < 0)
		return ;
	count = 0;
	while (s[count])
	{
		if (s[count] == ' ')
		{
			write(fd, " ",1);
			while (s[count] && s[count] == ' ')
				count++;
		}
		if (s[count] == '\0')
			break;
		ft_putchar_fd(s[count], fd);
		count++;
	}
}

t_bool		ft_echo(char **av)
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	if (nb_args(av) > 1)
	{
		while (av[i] && ft_strncmp(av[i], "-n", ft_strlen(av[i])) == 0)
		{
			option = 1;
			i++;
		}
		while (av[i])
		{
			ft_putstr_echo(av[i], 1);
			if (av[i + 1] && av[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option == 0)
		write(1, "\n", 1);
	return (true);
}