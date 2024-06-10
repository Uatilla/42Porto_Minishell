/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:09:38 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 20:52:28 by lebarbos         ###   ########.fr       */
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
	if (!ft_strcmp(cmd->argv[0], "export"))
		ret = export(sh, cmd, procs);
	return (ret);
}

t_execcmd	*get_exec_node(__attribute_maybe_unused__ t_shell *sh, t_cmd *node)
{
	t_execcmd	*execnode;

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
	return (false);
}

bool	isbuiltin_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5))
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
			printf("type: %d\n", cmd->n_type);
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
