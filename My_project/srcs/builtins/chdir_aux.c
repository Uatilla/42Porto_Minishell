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
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '.')
			count++;
		else
			count = 0;
		if (count >= 3)
		{
			printf("bash: cd: %s: No such file or directory\n", input);//HOW WRITE ON FD2
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_option(char *input)
{
	while (*input)
	{
		if (*input == '-')
		{
			printf("cd: '-' out of scope\n");//HOW WRITE ON FD2
			return (false);
		}
		input++;
	}
	return (true);
}

bool	sintax_valid_cd(char *cmd, char **argv, t_shell *sh)
{
	(void)sh;
	(void)cmd;
	if (!argv[1])
		return (true);
	if (!check_args(argv) || !check_dots(argv[1]) || !check_option(argv[1]))
		return (false);
	return (true);
}
