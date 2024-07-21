/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:00:17 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/21 03:10:52 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

char    *get_env(const char *key)
{
    t_env *current = g_global.e;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}


t_bool ft_cd(char **av)
{
    if (nb_args(av) == 1  || nb_args(av)  == 2 || strcmp(av[1], "~") == 0 )
    {
        if (chdir(get_env("HOME")) == -1)
        {
            write(2, "cd: HOME not set\n", 17);
            g_global.status = 1;
        }
    }
    else if (nb_args(av) > 2)
    {
        write(2, "cd\n", 3);
        write(2, "cd: too many arguments\n", 24);
        g_global.status = 1;
    }
    else
    {
        if (chdir(av[1]) == -1)
        {
            write(2, "cd\n", 3);
            write(2, "cd: no such file or directory: ", 30);
            write(2, av[1], ft_strlen(av[1]));
            write(2, "\n", 1);
            g_global.status = 1;
        }
    }

}
