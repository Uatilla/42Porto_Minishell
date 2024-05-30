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

void    run_exec(t_shell *sh, t_cmd *cmd)
{
    t_execcmd   *excmd;
    excmd = (t_execcmd *)cmd;
    if (excmd->argv[0] == 0)
        exit (1); //exit para limpar a lista?
    execve(excmd->command, excmd->argv, sh->paths);
    printf("exec %s failed\n", excmd->argv[0]);//ESCERVER NO FD 2.
    exit (1); //exit para limpar a lista?
}


void    exec_tree(t_shell *sh, t_cmd *cmd)
{
    
    t_redircmd  *rdcmd;
    t_pipecmd   *ppcmd;

    if (!cmd)
        clear_exit(sh, 1);
    if (cmd->n_type == N_EXEC)
    {
        run_exec(sh, cmd);
    }
    else if (cmd->n_type == N_REDIR)
    {
        rdcmd = (t_redircmd *)cmd;
        close(rdcmd->fd);
        if (open(rdcmd->file, rdcmd->mode) < 0)
        {
            printf("open %s failed\n", rdcmd->file);//ESCERVER NO FD 2.
            exit (1); //exit para limpar a lista?
        }
        exec_tree(sh, rdcmd->cmd);
    }
    else if (cmd->n_type == N_PIPE)
    {
        ppcmd = (t_pipecmd *)cmd;
        exec_tree(sh, ppcmd->left);
        exec_tree(sh, ppcmd->right);
        printf("PIPE\n");
    }
}