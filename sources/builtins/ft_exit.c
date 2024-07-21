/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:01:15 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/21 00:58:17 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int     nb_count(char **av)
{
    int i;

    i = 0;
    while (av[i])
        i++;
    return (i);
}
int     ft_isnumber(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

t_bool      ft_exit(char **av)
{
    int i = 1;
    if (nb_count(av) > 2)
    {
        write(2, "exit\n", 5);
        write(2, "exit: too many arguments\n", 25);
        g_global.status = 1;
        return (false);
    }
    else
    {

        if (nb_count(av) == 1)
        {
            write(2, "exit\n", 5);
            exit(g_global.status);
        }
        else
        {
            while (av[i])
            {
                if (ft_isnumber(av[i]) == false)
                {
                    write(2, "exit\n", 5);
                    write(2, "exit: numeric argument required\n", 33);
                    g_global.status = 255;
                    return (false);
                }
                i++;
            }
        }
        write(2, "exit\n", 5);
        exit((unsigned char)ft_atoi(av[1]));
    }
}
