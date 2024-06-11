/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:50:18 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 13:53:40 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_code(t_execcmd *exec)
{
	int i;
	int j;
	
	j = 0;
	while (exec->argv[1][j])
	{
		if (!ft_isdigit(exec->argv[1][j]))
			return (-1);
		j++;
	}
	i = ft_atoi(exec->argv[1]);
	if (i >= 0 && i <= 256)
		return (i);
	return (-1);
}

int	exit_bin(t_shell *sh, t_execcmd *exit_cmd, int procs)
{
	int ret;
	int exit_code;

	(void)procs;
	(void)sh;
	ret = 0;
	exit_code = 0;
	g_signo = 0;
	if (exit_cmd->argv[1])
		exit_code = is_exit_code(exit_cmd);
	if (exit_code >= 0)
		g_signo = exit_code;
	if (g_signo >= 0)
	{
		if (exit_code < 0 && exit_cmd->argv[1])
		{
			write(2, "exit: ", 7);
			custom_error(exit_cmd->argv[1], "numeric argument required", 2);
		}
		clear_exit(sh, g_signo);
	}
	else
		ret = g_signo;
	return (ret);
}