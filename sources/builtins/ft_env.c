/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:45:31 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 04:45:59 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool		ft_env(char **av)
{
	t_env	*tmp;

	tmp = g_global.e;
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
