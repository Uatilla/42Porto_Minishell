/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:50:18 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/13 18:44:15 by lebarbos         ###   ########.fr       */
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
			i = -2;
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
			i = -2;
			break ;
		}
		(*j)++;
	}
	return (i);
}

static	int	ft_get_len(long int n)
{
	long int	len;

	len = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = n *(-1);
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static	char	*inp_itoa(long int num, int len, char *str_ft_itoa)
{
	int	i;

	i = 1;
	if (num == 0)
		str_ft_itoa[0] = '0';
	while (num > 0)
	{
		str_ft_itoa[len - i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	return (str_ft_itoa);
}

char	*ft_lltoa(long long n)
{
	char	*str_ft_itoa;
	char	*str_ft_itoa2;
	long long	num;
	int		len;

	len = ft_get_len(n);
	str_ft_itoa = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_ft_itoa)
		return (NULL);
	if (n < 0)
	{
		num = n * (-1);
		str_ft_itoa[0] = '-';
	}
	else
		num = n;
	str_ft_itoa2 = inp_itoa(num, len, str_ft_itoa);
	str_ft_itoa2[len] = '\0';
	return (str_ft_itoa2);
}

int	is_exit_code(t_execcmd *exc)
{
	long long	i;
	int			j;
	// unsigned long nbr;

	j = 0;
	i = check_first_char(exc, &j);
	if (i != -2)
		i = check_digits(exc, &j);
	if (i != -2)
	{
		i = ft_atol(exc->argv[1]);
		printf("%lld\n", i);
		if (ft_strcmp(ft_lltoa(i), exc->argv[1]))
			return (-1);
		return (/*(unsigned long long)*/i/* % 256*/);
	}
	return (-2);
}

int	exit_bin(t_shell *sh, t_execcmd *exit_cmd, int procs)
{
	long long	exit_code;
	int			nbr_args;

	
	// long long	exit_code;
	// int			nbr_args;

	// nbr_args = 0;
	// exit_code = 0;
	// while (exit_cmd->argv[nbr_args])
	// 	nbr_args++;
	// if (exit_cmd->argv[1])
	// {
	// 	exit_code = is_exit_code(exit_cmd);
	// 	if (exit_code < 0)
	// 	{
	// 		printf("OI\n");
	// 		if (procs == TREE)
	// 		{
	// 			write(2, "exit: minishell: ", 18);
	// 			custom_error(NULL, exit_cmd->argv[1],
	// 				"numeric argument required", 2);
	// 		}
	// 		if (exit_code == -2)
	// 			exit_code = 2;
	// 	}
	// }
	// if (nbr_args > 2)
	// {
	// 	if (procs == PARENT)
	// 	{
	// 		custom_error("minishell: ", exit_cmd->argv[0], "too many arguments", 1);
	// 	}
	// }
	// printf("exit = %lld\n", exit_code);
	// g_signo = exit_code;
	// printf("g_signo = %d\n", g_signo);
	// if (procs == PARENT)
	// {
	// 	printf("exit\n");	
	// 	clear_exit(sh, g_signo);
	// }
	// return (g_signo);
}


// exit numero grande - nao funciona