/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:46:43 by akajjou           #+#    #+#             */
/*   Updated: 2024/05/24 17:06:53 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniHell.h"


int     first_pipe_checker(token_ptr tokens_list)
{
    token_ptr   tmp;

    tmp = tokens_list;
    if (tmp->token_type == 1)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        return 1;
    }
    while (tmp)
    {
        if (tmp->token_type == 1)
        {
            if (tmp->token_type == 0)
                while (tmp->next && tmp->next->token_type == 0)
                    tmp = tmp->next;
            if (tmp->next == NULL || tmp->next->token_type == 1)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                return 1;
            }
        }
        tmp = tmp->next;
    }
    return 0;
}
int     last_pipe_checker(token_ptr tokens_list)
{
    token_ptr   tmp;

    tmp = tokens_list;
    while (tmp->next->next)
        tmp = tmp->next;
    printf("tmp->order = %d\n", tmp->order);
    exit(0);
    tmp = tmp->previous;
    if (tmp->token_type == 0)
        while (tmp->order != 1 && tmp->previous->token_type == 0)
            tmp = tmp->previous;
    if (tmp->token_type == 1)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        return 1;
    }
    return 0;
}

int     pipe_checker(token_ptr tokens_list)
{
    token_ptr  tmp = tokens_list;

        tmp = tmp->next;
        tmp = tmp->next;
        tmp = tmp->next;
    while (tmp->order >= 1)
    {
        printf("%s\n",tmp->token);
        tmp = tmp->previous;
    }
        exit (0);
    if (first_pipe_checker(tokens_list) == 1) // check for the first pipe and double pipe
        return 1;
    if (last_pipe_checker(tokens_list) == 1) // check for the last pipe
        return 1;
    return 0;
}