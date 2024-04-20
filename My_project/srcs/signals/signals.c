/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:18:48 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/20 15:18:49 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    refresh_front(void)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    sigint_handler(int signo)
{
    if (signo == SIGINT)
    {
        g_signo = 130;
        refresh_front();
    }
}

void    reset_signal(void)
{
    signal(SIGINT, sigint_handler);
    //signal(SIGQUIT, SIG_IGN);
}