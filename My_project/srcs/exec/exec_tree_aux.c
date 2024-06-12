/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:35:49 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 17:41:22 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_file(char *file)
{
	if (ft_strchr(file, '/'))
		return (true);
	return (false);
}

bool	is_directory(char	*cmd)
{
	struct stat	path_stat;

	ft_bzero(&path_stat, sizeof(struct stat));
	stat(cmd, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

void	create_pipe(int p[2], t_shell *sh)
{
	if (pipe(p) < 0)
		clear_exit(sh, 1);
}

void	run_pipe_child(t_shell *sh, t_cmd *cmd, int p[2], int child)
{
	if (child == 1)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(sh, ((t_pipecmd *)cmd)->left);
	}
	else if (child == 2)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(sh, ((t_pipecmd *)cmd)->right);
	}
}

bool	handle_command_errors(t_execcmd *excmd)
{
	bool	ret;

	ret = true;
	if (!excmd->command)
	{
		if (!excmd->command && excmd->argv[0] && !isbuiltin(excmd->argv[0]))
		{
			if (is_file(excmd->argv[0]))
				custom_error("bash: ", excmd->argv[0], "No such file or directory", 127);
			else
				custom_error("bash: ", excmd->argv[0], "command not found", 127);
			ret = false;
		}
		else if (!access(excmd->argv[0], X_OK) || (excmd->argv[0] && is_directory(excmd->argv[0])))
		{
			custom_error("bash: ", excmd->argv[0], "Is a directory", 126);
			ret = false;
		}
	}
	return (ret);
}
