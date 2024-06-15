/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:20:22 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/14 16:49:32 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_unset(char **cmd, int procs, int argc)
{
	int	j;
	int	ret;

	ret = 0;
	if (cmd[argc][0] == '-' && !cmd[argc][2] && argc == 1)
	{
		if (procs == TREE)
			custom_error("minishell: unset: ", cmd[argc],
				"invalid option\nunset: usage: unset [name ...]", 2);
		return (2);
	}
	j = 2;
	while (cmd[argc][j])
	{
		if (!ft_isalpha(cmd[argc][1]) && cmd[argc][1] != '_')
			ret = 1;
		while (cmd[argc][j])
		{
			if (!ft_isalnum(cmd[argc][j]) && cmd[argc][1] != '_')
				ret = 1;
			j++;
		}
	}
	return (ret);
}

int	unset(t_shell *sh, t_execcmd *cmd, int procs)
{
	int		argc;
	t_list	*node;
	t_env	*env_node;
	int		ret;

	argc = 1;
	ret = 0;
	while (cmd->argv[argc])
	{
		ret = check_unset(cmd->argv, procs, argc);
		if (ret == 1 && procs == TREE)
			custom_error("minishell: ", cmd->argv[argc],
				": not a valid identifier", 1);
		if (ret == 0)
		{
			node = find_env_node(sh->env_lst, cmd->argv[argc]);
			if (node != NULL)
			{
				env_node = ((t_env *)(node->content));
				env_node->visible = false;
			}
		}
		argc++;
	}
	return (g_signo);
}
