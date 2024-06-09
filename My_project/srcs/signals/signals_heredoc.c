/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:18:30 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/09 11:32:09 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		// printf("\n");
		g_signo = 130;
		rl_replace_line("", 0);
		// rl_on_new_line();
		exit(g_signo);
	}
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}
