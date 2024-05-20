/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:29:00 by akajjou           #+#    #+#             */
/*   Updated: 2024/05/19 17:29:16 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniHell.h"

void   handler(int signum)
{
    write(STDOUT, "\n", 1);
    write(STDOUT, "kssh$ ", 6);
}

void   signal_handler()
{
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    signal(SIGTSTP, handler);
}