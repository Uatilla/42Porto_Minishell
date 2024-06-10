/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:32:00 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/10 15:32:02 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_word(char *word)
{
	int	i;

	i = 1;
	while (word[i])
	{
		if (word[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	check_flag(char **argv)
{
	int	argc;

	argc = 1;
	while (argv[argc])
	{
		if (argv[argc][0] == '-')
		{
			if (!check_word(argv[argc]))
				return (argc);
		}
		else
			return (argc);
		argc++;
	}
	return (1);
}

void	exec_echo(char **argv, int argc)
{
	bool	flag;

	flag = true;
	if (argc == 1)
		flag = false;
	while (argv[argc])
	{
		printf("%s", argv[argc]);
		if (argv[argc + 1])
			printf(" ");
		argc++;
	}
	if (!flag)
		printf("\n");
}

int	echo(t_shell *sh, t_execcmd *cmd)
{
	int	print_pos;

	print_pos = 0;
	(void)sh;
	(void)cmd;
	g_signo = 0;
	print_pos = check_flag(cmd->argv);
	exec_echo(cmd->argv, print_pos);
	return (g_signo);
}
