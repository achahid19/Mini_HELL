/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:01:15 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/20 19:01:29 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void    ft_exit(char **av)
{
    int i;

    i = 0;
    if (av[1])
    {
        if (av[2])
        {
            printf("exit\n");
            printf("minishell: exit: too many arguments\n");
            g_global.status = 1;
            return ;
        }
        while (av[1][i])
        {
            if (!ft_isdigit(av[1][i]))
            {
                printf("exit\n");
                printf("minishell: exit: %s: numeric argument required\n", av[1]);
                g_global.status = 255;
                return ;
            }
            i++;
        }
        g_global.status = ft_atoi(av[1]);
    }
    else
        g_global.status = 0;
    printf("exit\n");
    exit(g_global.status);
}