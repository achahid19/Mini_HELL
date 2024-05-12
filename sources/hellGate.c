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


int main(int ac, char **av, char **envp)
{
	char	*user_input;
	char	*tokens;

	while (true)
	{
		user_input = readline("kssh$ ");
		// tokenization of retrived intput
		tokens = lexer(user_input);
		printf("str: %s\n", user_input);
		free(user_input);
	}
}
