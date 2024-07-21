/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:23:02 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/21 20:15:07 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
 

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
    int		status;
	int		signal;
	int     flag;
    t_env   *e;
}	t_global;

extern t_global g_global;

#endif /* GLOBAL_H */
