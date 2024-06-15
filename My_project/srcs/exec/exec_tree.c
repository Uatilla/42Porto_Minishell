/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:02:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/15 20:00:34 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_shell *sh, t_execcmd *excmd)
{
	int	status;
	int	pid;

	status = 0;
	pid = 0;
	set_main_signal();
	if (isbuiltin(excmd->argv[0]))
		g_signo = execute_builtin(sh, excmd, TREE);
	else
	{
		pid = fork1(sh);
		if (pid == 0)
			ft_execve(sh, excmd);
	}
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_signo = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_signo = 128 + WTERMSIG(status);
	}
	set_signals();
}

void	run_exec(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*excmd;

	excmd = (t_execcmd *)cmd;
	if (handle_command_errors(excmd))
	{
		if (excmd->argv[0] && !is_directory(excmd->argv[0]))
			execute_command(sh, excmd);
	}
	else if (excmd->argv[0] && !ft_strcmp(excmd->argv[0], "exit") \
			&& sh->nbr_pipes == 0)
		g_signo = 0;
	clear_exit(sh, g_signo);
}

void	run_redir(t_shell *sh, t_cmd *cmd)
{
	t_redircmd	*rdcmd;

	rdcmd = (t_redircmd *)cmd;
	close(rdcmd->fd);
	if (rdcmd->file[0] == '$' && get(cmd->curr_tkn_pos)->state != IN_SQUOTES)
	{
		custom_error("minishell: ", rdcmd->file, "ambigous redirec", 1);
		clear_exit(sh, g_signo);
	}
	if (open(rdcmd->file, rdcmd->mode, rdcmd->perm) < 0)
	{
		g_signo = 1;
		write(2, "minishell: ", 12);
		perror(rdcmd->file);
		clear_exit(sh, g_signo);
	}
	exec_tree(sh, rdcmd->cmd);
}

void	run_pipe(t_shell *sh, t_cmd *cmd)
{
	int	p[2];
	int	status;
	int	pid1;
	int	pid2;

	create_pipe(p, sh);
	pid1 = fork1(sh);
	if (pid1 == 0)
		run_pipe_child(sh, cmd, p, 1);
	pid2 = fork1(sh);
	if (pid2 == 0)
		run_pipe_child(sh, cmd, p, 2);
	close(p[0]);
	close(p[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		g_signo = WEXITSTATUS(status);
	clear_exit(sh, g_signo);
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
