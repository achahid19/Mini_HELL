/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_checher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:35:45 by akajjou           #+#    #+#             */
/*   Updated: 2024/06/03 18:36:11 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"

int     parenthesis_checker(token_ptr tokens_list)
{
    token_ptr   tmp;
    int         count;

    tmp = tokens_list;
    count = 0;
    while (tmp)
    {
        if (tmp->token_type == 7)
            count++;
        if (tmp->token_type == 6)
            count--;
        if (count < 0)
        {
            ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
            return 1;
        }
        tmp = tmp->next;
    }
    if (count > 0)
    {
        ft_putstr_fd("syntax error near unexpected token `('\n", 2);
        return 1;
    }
    return 0;
}