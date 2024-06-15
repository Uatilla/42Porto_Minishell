/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:50:18 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 14:04:53 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_code(char *nbr)
{
	long long	i;
	char		*nbr_converted;

	i = ft_atol(nbr);
	nbr_converted = ft_lltoa(i);
	if (ft_strcmp(nbr_converted, nbr))
	{
		free(nbr_converted);
		return (false);
	}
	free(nbr_converted);
	return (true);
}

bool	is_valid_number(char *nbr, long long *exit_code)
{
	int	i;

	i = 0;
	if ((nbr[0] == '-' || nbr[0] == '+'))
	{
		i++;
		if (nbr[1] == '\0')
			return (false);
	}
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (false);
		i++;
	}
	if (!ft_strcmp(nbr, "-9223372036854775808") || is_exit_code(nbr))
	{
		*exit_code = ft_atol(nbr);
		return (true);
	}
	else
	{
		*exit_code = 2;
		return (false);
	}
}

bool	is_valid_exit(t_shell *sh, t_execcmd *cmd, long long *e_code, int procs)
{
	int		nbr_args;

	(void)sh;
	nbr_args = 0;
	while (cmd->argv[nbr_args])
		nbr_args++;
	if ((cmd->argv[1] && !is_valid_number(cmd->argv[1], e_code))
		|| !*cmd->argv[1])
	{
		if (procs == PARENT)
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->argv[1]);
		*e_code = 2;
		return (true);
	}
	if (nbr_args > 2)
	{
		*e_code = 1;
		if (procs == PARENT)
			printf("minishell: exit: too many arguments\n");
		return (false);
	}
	return (true);
}

int	exit_bin(t_shell *sh, t_execcmd *exit_cmd, int procs)
{
	long long	exit_code;
	bool		should_exit;

	exit_code = 0;
	if (procs == PARENT && sh->nbr_pipes == 0)
		printf("exit\n");
	if (!exit_cmd->argv[1])
	{
		should_exit = true;
		exit_code = 0;
	}
	else
	{
		should_exit = is_valid_exit(sh, exit_cmd, &exit_code, procs);
		g_signo = (unsigned int)exit_code % 256;
	}
	if (should_exit && procs == PARENT)
	{
		if (exit_cmd)
			free_tree((t_cmd *)exit_cmd);
		clear_exit(sh, g_signo);
	}
	return (g_signo);
}
