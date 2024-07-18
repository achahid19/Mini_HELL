/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:32:51 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/18 16:39:44 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

t_bool		ft_export(char **av, t_var *data)
{
    int i;

    if (!av[1])
    {
        // Print all exported variables
        i = 0;
        while (data->env[i])
        {
            printf("%s\n", data->env[i]);
            i++;
        }
    }
    else
    {
        // Export new variables
        i = 1;
        while (av[i])
        {
            // Check if the variable is already exported
            if (is_exported(av[i], data->env))
            {
                // Update the value of the existing variable
                update_exported_variable(av[i], data->env);
            }
            else
            {
                // Add the new variable to the exported variables
                add_exported_variable(av[i], data);
            }
            i++;
        }
    }
    return (true);
   
}