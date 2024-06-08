/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:18:48 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/08 12:21:26 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sigint_child_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(1, "\n", 1);
		return ;
	}
	else if (signo == SIGQUIT)
	{
		g_signo = 131;
		write(1, "Quit (core dumped)\n", 19);
		//printf("Quit (core dumped)\n");
	}
}

void	set_child_signals(void)
{
	signal(SIGINT, sigint_child_handler); //ctrl+c
	signal(SIGQUIT, sigint_child_handler); //ctrl+\/
}

void	set_main_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//na situacao cat nao pode ter redisplay
	}
}
void	set_signals(void)
{
		signal(SIGINT, sigint_handler); //ctrl+c
		signal(SIGQUIT, SIG_IGN); //ctrl+\/
		signal(SIGTSTP, SIG_IGN);
}

void	sigint_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		printf("MSG DO SIGNAL HANDLER bash: warning: here-document delimited by end-of-file\n");
		exit(130);
	}
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}