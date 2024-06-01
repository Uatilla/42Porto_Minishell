/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:02:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/01 19:33:27 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_exec(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*excmd;

	excmd = (t_execcmd *)cmd;
	if (!excmd->command)
	{
		//ft_putstr_fd(excmd->argv[0] & "command not found\n", 2);
		custom_error(excmd->argv[0], "command not found", 1);
		// printf("%s: command not found\n", excmd->argv[0]);//ESCERVER NO FD 2.
		exit (1);
	}
	if (execve(excmd->command, excmd->argv, sh->paths) == -1)
		printf("execve() didn't worked.\n");//ESCERVER NO FD 2.
	exit (1); //exit para limpar a lista?
}

void	run_redir(t_shell *sh, t_cmd *cmd)
{
	t_redircmd	*rdcmd;

	rdcmd = (t_redircmd *)cmd;
	close(rdcmd->fd);
	if (open(rdcmd->file, rdcmd->mode, rdcmd->perm) < 0)
	{
		printf("bash: %s: No such file or directory\n", rdcmd->file);//ESCERVER NO FD 2.
		exit (1); //exit para limpar a lista?
	}
	exec_tree(sh, rdcmd->cmd);
}

void	run_pipe(t_shell *sh, t_cmd *cmd)
{
	int	p[2];

	if (pipe(p) < 0)
		clear_exit(sh, 1);
	if (fork1(sh) == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(sh, ((t_pipecmd *)cmd)->left);
	}
	if (fork1(sh) == 0)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(sh, ((t_pipecmd *)cmd)->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	exit(0);
}

void	exec_tree(t_shell *sh, t_cmd *cmd)
{
	if (!cmd)
		clear_exit(sh, 1);
	if (cmd->n_type == N_EXEC)
		run_exec(sh, cmd);
	else if (cmd->n_type == N_REDIR)
		run_redir(sh, cmd);
	else if (cmd->n_type == N_PIPE)
		run_pipe(sh, cmd);
}
