/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/19 02:08:38 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/miniHell.h"

void   handler(int signum)
{
    write(STDOUT, "\n", 1);
    write(STDOUT, "kssh$ ", 6);
}

void   signal_handler()
{
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    signal(SIGTSTP, handler);
}
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
        if (strcmp(user_input,"\0") != 0) // for history
            add_history(user_input);
		tokens_list = lexer(user_input);
        if (parser_tokens(tokens_list) == 1)
            continue;
		free(user_input);
	}
}
