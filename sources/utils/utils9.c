/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:21:45 by akajjou           #+#    #+#             */
/*   Updated: 2024/08/29 18:33:37 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	handler_2(int signum)
{
	(void)signum;
	g_global.child_signal = 1;
	write(1, "\n", 1);
}

void	handler_3(int signum)
{
	(void)signum;
	g_global.child_signal = 2;
	write(1, "\n", 1);
}

void	ft_strncpy(char *dst, char const *s, int bytes)
{
	int	count;

	count = 0;
	while (count < bytes)
	{
		dst[count] = s[count];
		count++;
	}
	dst[count] = '\0';
}

void	ft_underscore(char *av)
{
	t_env	*tmp;

	tmp = g_global.e;
	if (av == NULL)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(av);
			return ;
		}
		tmp = tmp->next;
	}
}

void	shlvl_init(void)
{
	t_env	*tmp;
	char	*shlvl;

	tmp = g_global.e;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			if (ft_strcmp(tmp->value, "999") == 0)
			{
				free(tmp->value);
				printf("warning: shell level (999) too high, resetting to 1\n");
				tmp->value = ft_strdup("1");
				return ;
			}
			shlvl = ft_itoa(ft_atoi(tmp->value) + 1);
			free(tmp->value);
			tmp->value = ft_strdup(shlvl);
			free(shlvl);
			return ;
		}
		tmp = tmp->next;
	}
}
