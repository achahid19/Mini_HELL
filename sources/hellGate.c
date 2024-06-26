/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/06/08 21:13:06 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

/**
 * $() - Error
 * (pwd) - should be threated. as well as ((((cmd)))). (akajjou's work)
 * 
 * Optimize the token list
 * 	1 - skip all spaces and tokens with length == 0. (DONE)
 * 	2 - reorder the list.
 * 
 * TODO -> parenthisis ??
 * Syntax's Algo.
 * 
 * <>ls, problem for parser fail.
 * >>>ls, add for parse.
 * >><<ls, also
 * 
 * ls | $CMD ; error or not ?
 * 
 * "" -> bash command not found!
 * so must add "" and '' as commands if their is no command (fixed)
 * 
 * ""'ls'.
 * kssh$ echo "hello"no
 * hello no
 *
 * need spaces for execution.
 * 
 * if string == 0 need to make "" or '' as strings.
 * 
 * kssh$ "l""s"<etst     "ls".   hello"$PWDno"  "c""a""t" < filename.
 * 
 * "cat"<test"-e", touch '',
 * 
 * >>EOF"" ""ls
 * 
 * if an error occurs (syntax errro) re-prompt
*/
/**
 * 1st - cmd not found ! fix it. (in progress).
 * 2d - ls """"arg. (fixed).
 * 3th - quotes as commands -> pass a null terminating string (strdup).
 * 4th - norminette
 * 5th - leaks.
 * 
 * ls"""  """''"la"""""'' (fixed).
 * --->ls  la
 * garbage_objs  includes	libft  Makefile  miniHell  sources -> cmd not found.
 * 
 * for akkajou -> special char + quotes == error e.g (> "", < ''...) (no such file or dir.).
 * unless for heredoc << "" must prompt.
 * 
 * TODO LIST:
 * fix leaks (fixed).
 * strdup for quotes ("" or '').(fixed).
 * fix pipe (progress).
 * norminette.
 * handle input-output stream.
 * cat /dev/random | sleep 1
 * ls|"". TODO fix cmd not found.
*/
void	check_tokens(token_ptr print_tk)
{
	while (print_tk != NULL)
	{
		printf("------------------------------\n");
		printf("token: %s\n", print_tk->token);
		//printf("order: %d\n", print_tk->order);
		printf("type: %d\n", print_tk->token_type);
		//printf("lenght: %d\n", print_tk->token_length);
		/* if (print_tk->previous != NULL)
			printf("previous: %s\n", print_tk->previous->token);
		else if (print_tk->previous == NULL)
			printf("previous: NULL\n"); */
		printf("------------------------------\n");
		print_tk = print_tk->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	token_ptr	tokens_list;

	signal_handler();
	while (true)
	{
		if (isatty(STDIN_FILENO) == true)
			user_input = readline("kssh$ ");
		if (user_input == NULL)
			exit(EXIT_SUCCESS);
		if (ft_strncmp(user_input, "\0", 1) != 0)
			add_history(user_input);
		tokens_list = lexer(user_input);
		// add heredoc handler here.
		if (parser_tokens(tokens_list) == false)
		{
			free_all(tokens_list, user_input, NULL);
			continue;
		}
		tokens_expander(tokens_list, envp);
		tokens_list_optimizer(&tokens_list);
		syntax_algo(tokens_list);
		executor(tokens_list, envp, user_input);
		//check_tokens(tokens_list);
		free_all(tokens_list, user_input, NULL);
	}
	return (EXIT_SUCCESS);
}
