/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:46:39 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/12 13:38:27 by lebarbos         ###   ########.fr       */
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
			perror("bash: cd");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_option(char *input)
{
	if (*input == '-')
	{
		custom_error("bash: ", "cd", "'-' out of scope", 0);
		return (false);
	}
	input++;
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
