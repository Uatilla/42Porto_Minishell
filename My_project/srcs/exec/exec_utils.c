/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:56:47 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 20:00:14 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execve(t_shell *sh, t_execcmd *excmd)
{
	set_child_signals();
	if (execve(excmd->command, excmd->argv, sh->envp) == -1)
	{
		perror(excmd->command);
		if (access(excmd->argv[0], X_OK))
			clear_exit(sh, 126);
		exit(EXIT_FAILURE);
	}
}
