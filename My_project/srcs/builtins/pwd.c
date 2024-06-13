/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:01:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/12 19:22:30 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	sintax_valid_pwd(char *cmd, char **argv, t_shell *sh)
{
	(void)sh;
	(void)cmd;
	if (!argv[1])
		return (true);
	if (!(check_args(argv)))
	{
		if (argv[1][0] == '-')
		{
			if ((argv[1][1] == 'P' || argv[1][1] == 'L') \
				&& (only_white(argv[1], 2)))
			{
				custom_error("minishell: ", "pwd", "flags are out of scope", 0);
				return (false);
			}
			else
			{
				perror("minishell: pwd");
				g_signo = 2;
				return (false);
			}
		}
		else
			return (true);
	}
	return (true);
}

void	exec_pwd(t_shell *sh)
{
	char	pwd[PATH_MAX];

	(void)sh;
	if ((getcwd(pwd, sizeof(pwd)) == NULL))
	{
		perror("pwd error:");
		g_signo = 2;
	}
	else
		printf("%s\n", pwd);
}

int	pwd(t_shell *sh, t_execcmd *cmd)
{
	(void)sh;
	(void)cmd;
	g_signo = 0;
	if (!sintax_valid_pwd(cmd->argv[0], cmd->argv, sh))
		return (g_signo);
	else
		exec_pwd(sh);
	return (g_signo);
}
