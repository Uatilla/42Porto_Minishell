/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:46:39 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/09 20:46:42 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_dots(char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == '.')
			count++;
		else
			count = 0;
		if (count >= 3)
			return (false);
		input++;
	}
	return (true);
}

bool	check_option(char *input)
{
	while (*input)
	{
		if (*input == '-')
			return (false);
		input++;
	}
	return (true);
}

bool	sintax_valid_cd(char *cmd, char **argv, t_shell *sh)
{
	int	argc;

	(void)sh;
	(void)cmd;
	if (!argv[1])
		return (true);
	argc = 0;
	while (argv[argc])
	{
		if (argc > 1)
			return (false);
		argc++;
	}
	if (!check_dots(argv[1]) || !check_option(argv[1]))
		return (false);
	return (true);
}
