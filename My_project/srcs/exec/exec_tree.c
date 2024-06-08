/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:02:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/07 15:03:11 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_file(char *file)
{
	if (file[0] == '/' || !ft_strncmp(file, "./", 2))
		return (true);
	else if (ft_strnstr(file, ".sh", ft_strlen(file))
		&& ft_strchr(file, '/'))
		return (true);
	return (false);
}

/*void	run_exec(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*excmd;

	excmd = (t_execcmd *)cmd;
	if (!excmd->command && excmd->argv[0])
	{
		if (is_file(excmd->argv[0]))
			custom_error(excmd->argv[0], "No such file or directory", 127);
		else
			custom_error(excmd->argv[0], "command not found", 127);
		// exit (g_signo);
	}
	else if (excmd->argv[0])
	{
		if (execve(excmd->command, excmd->argv, sh->envp) == -1)
			perror(excmd->command);
	}
	exit (g_signo);
}*/

void	run_exec(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*excmd;
	int	status;

	excmd = (t_execcmd *)cmd;
	if (!excmd->command && excmd->argv[0])
	{
		if (is_file(excmd->argv[0]))
			custom_error(excmd->argv[0], "No such file or directory", 127);
		else
			custom_error(excmd->argv[0], "command not found", 127);
		// exit (g_signo);
	}
	else if (excmd->argv[0])
	{
		if (fork1(sh) == 0)
		{
			if (execve(excmd->command, excmd->argv, sh->envp) == -1)
				perror(excmd->command);
		}
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			g_signo = WEXITSTATUS(status);
	}
	exit (g_signo);
}

void	run_redir(t_shell *sh, t_cmd *cmd)
{
	t_redircmd	*rdcmd;

	rdcmd = (t_redircmd *)cmd;
	close(rdcmd->fd);
	if (open(rdcmd->file, rdcmd->mode, rdcmd->perm) < 0)
	{
		custom_error(rdcmd->file, "No such file or directory", 1);
		exit (g_signo);
	}
	exec_tree(sh, rdcmd->cmd);
}

void	run_pipe(t_shell *sh, t_cmd *cmd)
{
	int	p[2];
	int	status;
	int	pid1;
	int pid2;

	if (pipe(p) < 0)
		clear_exit(sh, 1);
	pid1 = fork1(sh);
	if (pid1 == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(sh, ((t_pipecmd *)cmd)->left);
	}
	// if (WIFEXITED(status))
	// 	g_signo = WEXITSTATUS(status);
	pid2 = fork1(sh);
	if (pid2== 0)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(sh, ((t_pipecmd *)cmd)->right);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		g_signo = WEXITSTATUS(status);
	exit(g_signo);
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
