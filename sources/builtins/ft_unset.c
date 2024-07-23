/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:31:47 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 20:20:55 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void    remove_variable(char *key)
{
    t_env *tmp;
    t_env *prev;

    tmp = g_global.e;
    prev = NULL;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
        {
            if (prev)
                prev->next = tmp->next;
            else
                g_global.e = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

t_bool		ft_unset(char **av)
{
    int i;

    i = 1;
    while (av[i])
    {
        if (is_exported(av[i]))
            remove_variable(av[i]);
        i++;
    }
    return (true);
}
