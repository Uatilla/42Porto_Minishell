/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:02:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/05/28 19:02:59 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_tree(t_shell *sh, t_cmd *cmd)
{
    t_execcmd   *execcmd;
    if (!cmd)
        clear_exit(sh, 1);
    if (cmd->n_type == N_EXEC)
    {
        printf("EXEC\n");
        execcmd = (t_execcmd *)cmd;
        if (execcmd->argv[0] == 0)
            exit (1);
        //exec(execcmd->argv[0], execcmd->argv);
    }
    else if (cmd->n_type == N_REDIR)
    {
        exec_tree(sh, ((t_redircmd *)(cmd))->cmd);
        printf("REDIR\n");

    }
    else if (cmd->n_type == N_PIPE)
    {
        exec_tree(sh, ((t_pipecmd *)(cmd))->left);
        exec_tree(sh, ((t_pipecmd *)(cmd))->right);
        printf("PIPE\n");
    }
}