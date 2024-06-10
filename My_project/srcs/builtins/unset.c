/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:20:22 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/10 17:20:23 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_shell *sh, t_execcmd *cmd)
{
	int		argc;
	t_list	*node;
	t_env	*env_node;

	argc = 0;
	while (cmd->argv[argc])
	{
		if (cmd->argv[argc][0] == '-')
			return (0);
		else
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
	return (0);
}
