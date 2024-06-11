/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:18:48 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/11 22:37:31 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_child_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		exit(g_signo);
	}
	else if (signo == SIGQUIT)
	{
		g_signo = 131;
		write(2, "Quit (core dumped)\n", 19);
		exit(g_signo);
	}
}

void	set_child_signals(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigint_child_handler);
}













void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		g_signo = 130;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
