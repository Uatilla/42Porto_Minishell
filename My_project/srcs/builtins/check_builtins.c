/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:09:38 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/09 09:29:22 by lebarbos         ###   ########.fr       */
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
	return (ret);
}

t_execcmd	*get_exec_node(t_shell *sh, t_list *tokens)
{
	t_cmd	*node;
	t_execcmd *execnode;

	node = parse_exec(sh, tokens);
	if (node->n_type == N_REDIR)
	{
		execnode = (t_execcmd *)((t_redircmd *)node)->cmd;
		free(((t_redircmd *)node)->file);
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
	else if(ft_strncmp(cmd, "pwd", 3) == 0)
		return(true);
	return(false);
}

bool	isbuiltin_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5) /* || !ft_strncmp(cmd, "env", 5) */)
		return (true);
	return (false);
}

void	builtins_parent(t_shell *sh)
{
	t_list	*tmp;
	bool	builtin;
	t_execcmd *execcmd;
	int i;

	execcmd = NULL;
	tmp = sh->token_lst;
	i = 0;
	while (tmp)
	{
		builtin = isbuiltin(get(tmp)->value);
		if (builtin)
		{
			execcmd = get_exec_node(sh, tmp);
			if (isbuiltin_parent(get(tmp)->value))
				execute_builtin(sh, execcmd, PARENT);
			while(execcmd->argv[i])
				free(execcmd->argv[i++]);
			free(execcmd->argv);
			free(execcmd->command);
			free(execcmd);
			return ;
		}
		tmp = tmp->next;
	}
}
