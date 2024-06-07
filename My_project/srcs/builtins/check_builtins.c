/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:09:38 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/07 19:06:29 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_builtin(__attribute_maybe_unused__ t_shell *sh, t_execcmd *cmd)
{
	char	*cmd_str;

	cmd_str = cmd->argv[0];
	if (ft_strcmp(cmd->argv[0], "env"))
		return ("builtin_env");
	return (NULL);
}

int	execute_builtin(t_shell *sh, t_execcmd *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->argv[0], "env"))
		ret = env(sh, cmd);
	return (ret);
}