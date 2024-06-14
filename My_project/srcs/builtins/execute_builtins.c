/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:17:15 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/13 20:17:16 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_cd(t_shell *sh, t_execcmd *cmd, int procs)
{
	int	ret;

	ret = 0;
	if (procs == PARENT)
		ret = change_dir(sh, cmd);
	else
		ret = g_signo;
	return (ret);
}

int	execute_builtin(t_shell *sh, t_execcmd *cmd, int procs)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->argv[0], "env"))
		ret = env(sh, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		ret = execute_builtin_cd(sh, cmd, procs);
	}
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ret = pwd(sh, cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		ret = echo(sh, cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ret = unset(sh, cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ret = export(sh, cmd, procs);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ret = exit_bin(sh, cmd, procs);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ret = export(sh, cmd, procs);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ret = exit_bin(sh, cmd, procs);
	return (ret);
}
