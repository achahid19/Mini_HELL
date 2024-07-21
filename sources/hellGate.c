/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/20 23:12:31 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"
#include "../includes/global.h"

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
 * ls|"". TODO fix cmd not found. (fixed)
 * weird leak for -> . as input lmao. also for "/"
 * 
 * // handle this case '"$?"' // do not expand for single quotes. (fixed).
 * change status to 130 after ctrl + c.
 * 
 * heredoc :
 * - segfault for enter key. e.g: << "" + Ctrl-d also SEGF.
 * - bug when exiting heredoc with Ctrl-c.
 * - for Ctrl-c fix re-prompting issue (like in interrupting a runnig command). (2 prompt displayed).
 * - expander for heredoc... not working yet.
 * - problem in -> e.g: cat <<test<<test1 -> SEGF
 * - SEGF in -> <<>>ls or <<>ls or >>>ls. (does not matter ls with space or not). Syntax error
 * - leaks to be FIXED.
 * 
 * SOME BUGS:
 * - "" -> command not found, but """" must do same thing. (fixed).
 * - fix exit code for redirictions failing. (in progress).
 * - add new line for syntax errors. (in progress).
 * - fix exit codes for syntax errors...
 * 
 * TO fix:
 * - bugs: 
 * 	1. cat <<aa>test, cat <<aa|ls, <<a<<b<<c... (DONE).
 * 		in case of space before special chars (<, |, <<...) its working normal. (urgent).
 * 	2. expand in heredoc... $PW, $USE... (poss fixed). (urgent). (DONE)
 * 	3. syntax errors: SEGF: cat <<<a, cat <<>a, cat >>>>a. (NOT DONE) -> e.g: cat <<>>a SEFG,
 *     >><<a must return syntax error, >>>a... (A LOT OF SYNTAX ERRORS ARE NOT HANDLED).
 * 	4. error for < "". no such file... (PROGRESS) (need explanation) (Multiple quotes)
 * 	5. after heredoc, ctrl+c has a changed behavior... (urgent). (PROGRESS) (DONE BUT STILL A VERY LIIITLE BUG \n).
 * 	6. << "". enter as delimeter. (urgent). (segf ctrl + c)
 *  7. expand $?. for heredoc (urgent). (DONE) (STILL BUGS TO FIX)
 *  8. close heredoc fds after execution is done.
 * 	   store all of them in an int array so we can freed them
 * 	   after execution is done. (DONE)
 *  9. dont expand in quotes. (PROGRESS)
 *  10. a lot of leaks. (urgent) (PROGRESS).
 * 	
 * 
 * Bult-ins bugs:
 * 	1. echo: e.g: echo -nl -> should be outputed. (PROGRESS) (fix)
 *  2. echo: e.g: echo -n-n-n -> should be outputed. (PROGRESS) (fix)
 *   
*/
static t_bool	ft_readline(char **user_input);
static void 	ft_unlink(token_ptr tokens_list);
static void		ft_init(char **envp, char **user_input);
static void		miniHell_helper(token_ptr tokens_list, char *user_input,
					char **envp, char **e);
void			check_tokens(token_ptr print_tk);

/**
 * main - Entry point
*/
int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	token_ptr	tokens_list;
	char		**e;

	ft_init(envp, &user_input);
	while (ft_readline(&user_input) == true)
	{
		e = transform_env();
		tokens_list = lexer(user_input);
		if (parser_tokens(tokens_list, g_global.e) == false)
		{
			free_all(tokens_list, user_input, e);
			continue ;
		}
		tokens_expander(tokens_list, e);
		tokens_list_optimizer(&tokens_list);
		if (tokens_list == NULL)
		{
			free_all(tokens_list, user_input, e);
			continue ;
		}
		miniHell_helper(tokens_list, user_input, envp, e);
	}
	return (EXIT_SUCCESS);
}

/**
 * ft_init -
 */
static void	ft_init(char **envp, char **user_input)
{
	signal_handler();
	init_global();
	g_global.e = init_env(envp);
	*user_input = NULL;
}

/**
 * ft_readline -
*/
t_bool	ft_readline(char **user_input)
{
	*user_input = readline("kssh$ ");
	if (*user_input == NULL)
	{
		if (isatty(STDIN) == true)
			printf("exit\n");
		free_global_env();
		exit(EXIT_SUCCESS);
	}
	return (true);
}

static void 	ft_unlink(token_ptr tokens_list)
{
	while (tokens_list)
	{
		if (tokens_list->token_type == 8 )
			if (ft_strncmp(tokens_list->token, "/tmp/heredoc_", 13) == 0)
				unlink(tokens_list->token);
		tokens_list = tokens_list->next;
	}
}

/**
 * miniHell_helper -
 */
static void	miniHell_helper(token_ptr tokens_list, char *user_input,
			char **envp, char **e)
{
	syntax_algo(tokens_list);
	//check_tokens(tokens_list);
	executor(tokens_list, envp, user_input);
	ft_unlink(tokens_list);
	free_all(tokens_list, user_input, e);
}

/**
 * check_tokens -
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
