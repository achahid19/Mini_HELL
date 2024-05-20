/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/20 16:47:14 by akajjou          ###   ########.fr       */
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
        printf("------------------------------\n");
        print_tk = print_tk->next;
    }
}

int main(int ac, char **av, char **envp)
{
	char        *user_input;
	token_ptr   tokens_list;

    signal_handler();
	while (true)
	{
        user_input = readline("kssh$ ");
        if (user_input == NULL) // for (ctrl + d)
            exit (1);
        if (strcmp(user_input,"\0") != 0) // for history
            add_history(user_input);
		tokens_list = lexer(user_input);
        check_tokens(tokens_list);
        if (parser_tokens(tokens_list) == 1)
            continue;
		free(user_input);
	}
}
