/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:21:45 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 23:30:53 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	handler_2(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	hendler_1(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
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