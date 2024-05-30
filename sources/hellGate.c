/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/05/29 06:37:50 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// handle $ sign for expansion then clean all mem leaks.
    // for $, chars to take (a..z, A..Z, '0'..'9', '_')
    // optimize get_token_length function

// Integrate dollar token for lexer

#include "../includes/miniHell.h"

void	check_tokens(token_ptr print_tk)
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
int	main(int ac, char **av, char **envp)
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
		tokens_expander(tokens_list, envp);
		// check_tokens(tokens_list);
		// exit(1);
		if (parser_tokens(tokens_list) == 1)
			continue;
		// build_in(tokens_list);
		free(user_input);
	}
}
