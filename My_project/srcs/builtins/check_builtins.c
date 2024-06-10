/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:09:38 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 12:28:24 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_builtin(t_shell *sh, t_execcmd *cmd)
{
	// char	*cmd_str;

	(void)sh;
	// cmd_str = cmd->argv[0];
	if (ft_strcmp(cmd->argv[0], "env"))
		return ("builtin_env");
	return (NULL);
}

int	execute_builtin(t_shell *sh, t_execcmd *cmd, bool tree)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->argv[0], "env"))
		ret = env(sh, cmd);
	if (!ft_strcmp(cmd->argv[0], "export"))
		ret = export(sh, cmd, tree);
	return (ret);
}

t_execcmd	*get_exec_node(t_shell *sh, t_cmd *node)
{
	// t_cmd	*node;
	t_execcmd *execnode;

	(void)sh;
	// node = parse_exec(sh, tokens);
	if (node->n_type == N_REDIR)
	{
		execnode = (t_execcmd *)((t_redircmd *)node)->cmd;
		// free(((t_redircmd *)node)->file);
	}
	else
		execnode = (t_execcmd *)node;
	return (execnode);
}

bool isbuiltin(char *cmd)
{
	if(ft_strncmp(cmd, "env", 5) == 0)
		return(true);
	else if(ft_strncmp(cmd, "exit", 4) == 0)
		return(true);
	else if(ft_strncmp(cmd, "cd", 2) == 0)
		return(true);
	else if(ft_strncmp(cmd, "export", 7) == 0)
		return(true);
	return(false);
}

bool	isbuiltin_parent(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5) /* || !ft_strncmp(cmd, "env", 5) */)
		return (true);
	return (false);
}

void	builtins_parent(t_shell *sh)
{
	t_list		*tmp;
	bool		builtin;
	t_execcmd	*execcmd;
	// int			i;
	t_cmd		*cmd;

	execcmd = NULL;
	tmp = sh->token_lst;
	// i = 0;
	while (tmp)
	{
		builtin = isbuiltin_parent(get(tmp)->value);
		if (builtin)
		{
			cmd = parse_exec(sh, tmp);
			execcmd = get_exec_node(sh, cmd);
			if (ft_strcmp(execcmd->argv[0], "export"))
				export_parent(sh, cmd);
			else
				execute_builtin(sh, execcmd, false);
			free_tree(cmd);
			return ;
		}
		tmp = tmp->next;
	}
}
