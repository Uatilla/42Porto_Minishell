/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:45:11 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 19:45:19 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exit(t_shell *sh, int status)
{
	int	i;

	i = 0;
	if (!sh)
		exit(EXIT_FAILURE);
	free_env_list(&sh->env_lst);
	free_token_list(&sh->token_lst);
	free(sh->index);
	if (sh->paths)
	{
		while (sh->paths[i])
		{
			free(sh->paths[i]);
			i++;
		}
		free(sh->paths);
	}
	if (sh->envp)
	{
		while (sh->envp[i])
			free(sh->envp[i++]);
	}
	rl_clear_history();
	exit(status);
}