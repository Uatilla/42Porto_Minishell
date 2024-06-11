/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:15:40 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/11 20:05:16 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_cmd *cmd)
{
	int			argc;
	t_execcmd	*execcmd;

	argc = 0;
	if (cmd->n_type == N_PIPE)
	{
		free_tree(((t_pipecmd *)(cmd))->left);
		free_tree(((t_pipecmd *)(cmd))->right);
		free((t_pipecmd *)(cmd));
	}
	else if (cmd->n_type == N_REDIR)
	{
		free_tree(((t_redircmd *)(cmd))->cmd);
		free((t_redircmd *)(cmd));
	}
	else if (cmd->n_type == N_EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		while (execcmd->argv[argc])
			free(execcmd->argv[argc++]);
		free(execcmd->argv);
		free(execcmd);
	}
}

	/*Clean all elements of the tree:
		*argv[]: From ft_strdup() fill_execcmd()
		cmd->argv[]: From the execcmd().
		Exec Node = cmd: From execcmd().
		Redir Node = cmd: From redircmd().
		Pipe Node = cmd: From pipecmd().
		*/