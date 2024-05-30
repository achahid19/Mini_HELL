/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:56:44 by akajjou           #+#    #+#             */
/*   Updated: 2024/05/29 11:04:37 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"

int     ft_echo(token_ptr tokens_list)
{
    token_ptr   tmp;
    int         i;

    tmp = tokens_list->next;
    i = 0;
    while (tmp)
    {
        if (i != 0)
            write(STDOUT, " ", 1);
        ft_putstr_fd(tmp->token, 1);
        tmp = tmp->next;
        i++;
    }
    write(STDOUT, "\n", 1);
    return 0;
}

void    build_in(token_ptr tokens_list)
{
    if (strcmp(tokens_list->token, "echo") == 0)
        ft_echo(tokens_list);
    // else if (ft_strcmp(tokens_list->token, "cd") == 0)
    //     ft_cd(tokens_list);
    // else if (ft_strcmp(tokens_list->token, "pwd") == 0)
    //     ft_pwd();
    // else if (ft_strcmp(tokens_list->token, "export") == 0)
    //     ft_export(tokens_list);
    // else if (ft_strcmp(tokens_list->token, "unset") == 0)
    //     ft_unset(tokens_list);
    // else if (ft_strcmp(tokens_list->token, "env") == 0)
    //     ft_env();
    // else if (ft_strcmp(tokens_list->token, "exit") == 0)
    //     ft_exit(tokens_list);
    // else
    //     ft_exec(tokens_list);
}
