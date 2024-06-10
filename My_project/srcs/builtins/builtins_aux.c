/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:09:29 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/10 14:09:30 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_args(char **input)
{
	int	argc;

	argc = 1;
	while (input[argc])
	{
		if (argc >= 2 && !ft_strcmp(input[0], "cd"))
		{
			printf("bash: cd: too many arguments\n");//WRITE ON FD2
			return (false);
		}
        else if(argc >= 1 && !ft_strcmp(input[0], "pwd"))
			return (false);
		argc++;
	}
	return (true);
}
