/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:29:00 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 23:34:53 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

void	ft_handler(int signum)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
	(void)signum;
}

void	handler_heredoc(int signum)
{
	write(STDOUT, "\n", 1);
	g_global.flag = 1;
	close(0);
	(void)signum;
}

void	ft_handler_heredoc(int signum)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
	(void)signum;
}

void	signal_handler(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
