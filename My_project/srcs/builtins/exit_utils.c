/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:11:59 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/14 10:33:39 by lebarbos         ###   ########.fr       */
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

static int	ft_countsize(long long nbr)
{
	int	size;

	size = 1;
	if (nbr < 0)
	{
		size++;
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		size++;
		nbr = nbr / 10;
	}
	return (size);
}

static void	ft_putnstr(long long n, char *str, int size)
{
	int	check;

	check = 0;
	str[size] = '\0';
	while (size > check)
	{
		if (n < 0)
		{
			str[0] = '-';
			n = -n;
			check++;
		}
		else
		{
			str[size - 1] = (n % 10) + '0';
			n = n / 10;
			size--;
		}
	}
}

char	*ft_lltoa(long long n)
{
	char	*str;
	int		size;

	size = ft_countsize(n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_putnstr(n, str, size);
	return (str);
}
