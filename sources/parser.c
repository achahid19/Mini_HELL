/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:47 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/23 18:49:14 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniHell.h"

int    ft_type_check(token_ptr tokens_list)
{
    if (pipe_checker(tokens_list) == 1)
        return 1;
    return 0;
}

int   parser_tokens(token_ptr tokens_list)
{
    if (tokens_list == NULL)
        return  0;
    if (ft_type_check(tokens_list) == 1)
        return 1;
    return 0;
}
