/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:08:50 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 12:31:46 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_parent(t_shell *sh, t_cmd *cmd)
{
	t_execcmd *exec;
	int		ret;

	exec = get_exec_node(sh, cmd);
	if (cmd->n_type == N_REDIR)
	{
		if (exec->argv[1])
			ret = export(sh, exec, false);
		else
			return (1);
	}
	else
		ret = export(sh, exec, false);
	return (ret);
}

int	export(t_shell *sh, t_execcmd *execcmd, bool tree)
{
	char	*key;
	char	*value;
	int i;

	i = 0;
	key = NULL;
	value = NULL;
	if (execcmd->argv[1])
	{
		while (execcmd->argv[1][i] && execcmd->argv[0][i] != '=')
			i++;
		key = ft_substr(execcmd->argv[1], 0, i);
		if (ft_strchr(execcmd->argv[1], '=') + 1 != (char *)0)
			value = ft_strdup(ft_strchr(execcmd->argv[1], '=') + 1);
		else
			value = NULL;
		if (!tree)
			att_env(sh, key, value);
	}
	if (tree)
		print_export(sh);
	return (0);
}