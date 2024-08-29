/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:33:03 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/22 22:45:06 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global.h"

t_global	g_global;

void	init_global(void)
{
	g_global.status = 0;
	g_global.flag = 0;
	g_global.eof = 1;
	g_global.ctrd = 0;
	g_global.child_signal = 0;
}
