/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:45:11 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 13:43:33 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exit(t_shell *sh, int status)
{
	if (!sh)
		exit(EXIT_FAILURE);
	free_env_list(&sh->env_lst);
	free_token_list(&sh->token_lst);
	free(sh->index);
	if (sh->paths)
		free_path(sh->paths);
	if (sh->envp)
		free_path(sh->envp);
	if (sh->cmd)
		free_tree(sh->cmd);
	rl_clear_history();
	exit(status);
}
