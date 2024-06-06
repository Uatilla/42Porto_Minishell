/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:18:48 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/21 20:27:23 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_front(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//na situacao cat nao pode ter redisplay
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		refresh_front();
	}
}

void	sigint_child_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		printf("oiut\n");
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	set_child_signals(void)
{
		signal(SIGINT, sigint_child_handler); //ctrl+c
}

void	set_signals(void)
{
		signal(SIGINT, sigint_handler); //ctrl+c
		signal(SIGQUIT, SIG_IGN); //ctrl+\/
		signal(SIGTSTP, SIG_IGN);
}
