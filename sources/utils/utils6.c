/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:20:30 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/20 21:20:31 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include "../../includes/global.h"

void	get_status();

/**
 * get_status -
 */
void	get_status()
{
	if (g_global.status == 256)
		g_global.status = 127;
	else if (g_global.status == 768)
		g_global.status = 1;
	else if (g_global.status == 32256)
		g_global.status = 126;
	else if (g_global.status == 512)
		g_global.status = 2;
	else if (g_global.status == 13)
		g_global.status = 0;
	else if (g_global.status == 127)
		g_global.status = 1;
}
