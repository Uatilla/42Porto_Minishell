/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:25:01 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/27 15:25:03 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if all the further positions are white space.*/
bool	only_white(char *input, int curr_pos)
{
	while (input[curr_pos])
	{
		if (ft_iswhitespace(input[curr_pos]))
			curr_pos++;
		else
			return (false);
	}
	return (true);
}

bool	is_a_pipe(char c)
{
	return (c == '|');
}

bool	is_a_bigger(char c)
{
	return (c == '>');
}

bool	is_a_smaller(char c)
{
	return (c == '<');
}

void	input_check(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("ERROR: MINISHELL can't receive inputs.\n", 2);
		clear_exit(NULL, 1);
	}
	if (!envp[0])
		ft_putstr_fd("ERROR: ENVIRONMENT VARIABLES are empty\n", 2);
}
