/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:50:18 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 19:22:30 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(const char *nptr)
{
	int			signal;
	long long	number;

	signal = 1;
	number = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
	{
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
		{
			signal = signal * (-1);
		}
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number *= 10;
		number += *nptr - 48;
		nptr++;
	}
	return (signal * number);
}

long long	check_first_char(t_execcmd *exc, int *j)
{
	long long	i;

	i = 0;
	if ((exc->argv[1][0] == '-' || exc->argv[1][0] == '+'))
	{
		if (!exc->argv[1][1])
			i = -1;
		(*j)++;
	}
	return (i);
}

long long	check_digits(t_execcmd *exc, int *j)
{
	long long	i;

	i = 0;
	while (exc->argv[1][*j])
	{
		if (!ft_isdigit(exc->argv[1][*j]))
		{
			i = -1;
			break ;
		}
		(*j)++;
	}
	return (i);
}

// long long	is_exit_code(t_execcmd *exc)
// {
// 	long long	i;
// 	int			j;

// 	j = 0;
// 	i = check_first_char(exc, &j);
// 	if (i != -1)
// 		i = check_digits(exc, &j);
// 	if (i != -1)
// 	{
// 		i = ft_atol(exc->argv[1]);
// 		if (i <= LONG_MAX && i >= LONG_MIN)
// 		{
// 			return ((unsigned long long)i);
// 		}
// 	}
// 	return (-1);
// }

int	is_exit_code(t_execcmd *exc)
{
	long long	i;
	int			j;

	j = 0;
	i = check_first_char(exc, &j);
	if (i != -1)
		i = check_digits(exc, &j);
	if (i != -1)
	{
		i = ft_atol(exc->argv[1]);
		if (i > LONG_MAX || i < LONG_MIN)
			return (-1);
		return ((unsigned int)i % 256);
	}
	return (-1);
}

int	exit_bin(t_shell *sh, t_execcmd *exit_cmd, int procs)
{
	long long	exit_code;
	int			ret;
	int			nbr_args;

	nbr_args = 0;
	ret = 0;
	exit_code = 0;
	while (exit_cmd->argv[nbr_args])
		nbr_args++;
	if (exit_cmd->argv[1])
	{
		exit_code = is_exit_code(exit_cmd);
		if (exit_code == -1)
		{
			if (procs == TREE)
			{
				write(2, "exit: minishell: ", 13);
				custom_error(NULL, exit_cmd->argv[1],
					"numeric argument required", 2);
			}
			exit_code = 2;
		}
	}
	if (nbr_args > 2)
	{
		if (procs == PARENT)
			custom_error("minishell: ", exit_cmd->argv[0], "too many arguments", 1);
		return (g_signo);
	}
	g_signo = exit_code % 256;
	if (procs == PARENT)
		clear_exit(sh, g_signo);
	return (g_signo);
}
