/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:09:38 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 14:42:05 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *sh, t_execcmd *cmd, int procs)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->argv[0], "env"))
		ret = env(sh, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		if (procs == PARENT)
			ret = change_dir(sh, cmd);
		else
			ret = g_signo;
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

t_execcmd	*get_exec_node(t_shell *sh, t_cmd *node)
{
	t_execcmd	*execnode;

	(void)sh;
	execnode = NULL;
	while (node->n_type == N_REDIR)
		node = ((t_redircmd *)node)->cmd;
	if (node->n_type == N_EXEC)
		execnode = (t_execcmd *)node;
	return (execnode);
}

bool	isbuiltin(char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	return (false);
}

bool	isbuiltin_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

void	builtins_parent(t_shell *sh)
{
	t_list		*tmp;
	bool		builtin;
	t_execcmd	*execcmd;
	t_cmd		*cmd;

	execcmd = NULL;
	tmp = sh->token_lst;
	while (tmp)
	{
		builtin = isbuiltin_parent(get(tmp)->value);
		if (builtin)
		{
			cmd = parse_exec(sh, tmp);
			execcmd = get_exec_node(sh, cmd);
			if (!ft_strcmp(execcmd->argv[0], "export"))
				export_parent(sh, cmd);
			else
				execute_builtin(sh, execcmd, PARENT);
			free_tree(cmd);
			return ;
		}
		tmp = tmp->next;
	}
}
