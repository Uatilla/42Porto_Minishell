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
	if (!word[i])
		return (false);
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
	if (!argv[argc])
		return (argc);
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
	int	printable_wrd;

	printable_wrd = 0;
	(void)sh;
	(void)cmd;
	g_signo = 0;
	printable_wrd = check_flag(cmd->argv);
	exec_echo(cmd->argv, printable_wrd);
	return (g_signo);
}
