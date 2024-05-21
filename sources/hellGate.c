/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahid- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/05 10:30:08 by achahid-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/miniHell.h"


void    check_tokens(token_ptr print_tk)
{
    while (print_tk != NULL)
    {
        printf("------------------------------\n");
        printf("token: %s\n", print_tk->token);
        printf("order: %d\n", print_tk->order);
        printf("type: %d\n", print_tk->token_type);
        printf("lenght: %d\n", print_tk->token_length);
        if (print_tk->previous != NULL)
            printf("previous: %s\n", print_tk->previous->token);
        else if (print_tk->previous == NULL)
            printf("previous: NULL\n");
        printf("------------------------------\n");
        print_tk = print_tk->next;
    }
}

int main(int ac, char **av, char **envp)
{
	char        *user_input;
	token_ptr   tokens_list;

	while (true)
	{
        user_input = readline("kssh$ ");
		// tokenization of retrived intput
		tokens_list = lexer(user_input);
        if (tokens_list == NULL)
            continue ;
        check_tokens(tokens_list);
		printf("str: %s\n", user_input);
		free(user_input);
	}
}
