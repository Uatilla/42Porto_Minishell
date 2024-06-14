/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:11:59 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/14 10:26:13 by lebarbos         ###   ########.fr       */
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

// static	int	get_len(long int n)
// {
// 	long int	len;

// 	len = 0;
// 	if (n == 0)
// 		return (1);
// 	else if (n < 0)
// 	{
// 		n = n *(-1);
// 		len++;
// 	}
// 	while (n > 0)
// 	{
// 		n = n / 10;
// 		len++;
// 	}
// 	return (len);
// }

// static	char	*n_itoa(long int num, int len, char *str_ft_itoa)
// {
// 	int	i;

// 	i = 1;
// 	if (num == 0)
// 		str_ft_itoa[0] = '0';
// 	while (num > 0)
// 	{
// 		str_ft_itoa[len - i] = num % 10 + '0';
// 		num = num / 10;
// 		i++;
// 	}
// 	return (str_ft_itoa);
// }

// char	*ft_lltoa(long long n)
// {
// 	char		*str_ft_itoa;
// 	char		*str_ft_itoa2;
// 	long long	num;
// 	int			len;

// 	len = get_len(n);
// 	str_ft_itoa = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str_ft_itoa)
// 		return (NULL);
// 	if (n < 0)
// 	{
// 		num = n * (-1);
// 		str_ft_itoa[0] = '-';
// 	}
// 	else
// 		num = n;
// 	str_ft_itoa2 = n_itoa(num, len, str_ft_itoa);
// 	str_ft_itoa2[len] = '\0';
// 	return (str_ft_itoa2);
// }


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
