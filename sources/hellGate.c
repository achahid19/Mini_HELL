/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellGate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:30:07 by achahid-          #+#    #+#             */
/*   Updated: 2024/07/28 23:47:58 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

static t_bool	ft_readline(char **user_input);
static void		ft_unlink(t_ptr tokens_list);
static void		ft_init(char **envp, char **user_input);
static void		minihell_helper(t_ptr tokens_list, char *user_input,
					char **e);

/**
 * notes -
 * ctrl-c in heredoc - fix exit status
 */

/**
 * main - Entry point
*/
int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_ptr		tokens_list;
	char		**e;

	(void)ac;
	(void)av;
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
		if (tokens_list == NULL)
		{
			free_all(tokens_list, user_input, e);
			continue ;
		}
		minihell_helper(tokens_list, user_input, e);
	}
	return (EXIT_SUCCESS);
}

/**
 * ft_init -
 */
static void	ft_init(char **envp, char **user_input)
{
	init_global();
	g_global.e = init_env(envp);
	shlvl_init();
	*user_input = NULL;
}

/**
 * ft_readline -
*/
t_bool	ft_readline(char **user_input)
{
	signal_handler();
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

static void	ft_unlink(t_ptr tokens_list)
{
	while (tokens_list)
	{
		if (tokens_list->token_type == leftred_token)
			if (ft_strncmp(tokens_list->token, "/tmp/heredoc_", 13) == 0)
				unlink(tokens_list->token);
		tokens_list = tokens_list->next;
	}
}

/**
 * miniHell_helper -
 */
static void	minihell_helper(t_ptr tokens_list, char *user_input,
				char **e)
{
	syntax_algo(tokens_list);
	executor(tokens_list, e, user_input);
	ft_unlink(tokens_list);
	free_all(tokens_list, user_input, e);
}

/**
 * check_tokens -
 */
/*void	check_tokens(t_ptr print_tk)
{
	while (print_tk != NULL)
	{
		printf("------------------------------\n");
		printf("token: %s\n", print_tk->token);
		printf("type: %d\n", print_tk->token_type);
		printf("order: %d\n", print_tk->order);
		printf("lenght: %d\n", print_tk->token_length);
		if (print_tk->previous != NULL)
			printf("previous: %s\n", print_tk->previous->token);
		else if (print_tk->previous == NULL)
			printf("previous: NULL\n");
		printf("------------------------------\n");
		print_tk = print_tk->next;
	}
}*/
