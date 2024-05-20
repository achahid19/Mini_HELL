/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:46:43 by akajjou           #+#    #+#             */
/*   Updated: 2024/05/20 01:56:58 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniHell.h"

int     double_pipe_checker(token_ptr tokens_list) // check if there is a double pipe
{
    token_ptr temp;
    
    temp = tokens_list;
    while (temp->next != NULL)
    {
        if (temp->token_type == 1 && temp->next->token_type == 1)
        {
            printf("bash: syntax error near unexpected token `|'\n");
            return 1;
        }
        else if (temp->token_type == 1 && temp->next->token_type == 0)
        {
            while (temp->next->token_type == 0 && temp->next != NULL)
                temp = temp->next;
            if (temp->next->token_type == 1)
            {
                printf("bash: syntax error near unexpected token `|'\n");
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int     last_pipe_checker(token_ptr tokens_list) // check if the last token is a pipe
{
    token_ptr temp;
    int pipe;
    
    temp = tokens_list;
    pipe = 0;
    while (temp->next != NULL)
    {
        if (temp->token_type == 1 )
            pipe++;        
        temp = temp->next;
    }
    if (temp->token_type == 1)
        pipe++;
    temp = tokens_list;
    while (temp->next != NULL)
    {
        if (temp->token_type == 1)
            pipe--;
        if (pipe == 0)
            break;
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return 1;
    }
    else if (temp->next->token_type == 0)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return 1;
    }
    
}

int     pipe_checker_first(token_ptr tokens_list) // check if the first token is a pipe & and skip ws
{
    token_ptr temp;
    
    temp = tokens_list;
    if (temp->token_type == 0)
        while (temp->token_type == 0 && temp->next != NULL)
            temp = temp->next;
    if (temp->token_type == 1)
    {
        printf("bash: syntax error near unexpected token `%s'\n",temp->token);
        return 1;
    }
    if (double_pipe_checker(tokens_list) == 1 || last_pipe_checker(tokens_list) == 1)
        return 1;

}

int     pipe_checker(token_ptr tokens_list)
{
    if (pipe_checker_first(tokens_list) == 1)
        return 1;
    
}