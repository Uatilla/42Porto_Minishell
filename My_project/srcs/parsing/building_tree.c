/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:25:01 by uviana-a          #+#    #+#             */
/*   Updated: 2024/05/15 20:25:30 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execcmd*  bld_exec_nd(void)
{
    t_execcmd   *cmd;


    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL); //IF THIS RETURNS AN ERROR, SHOULD CALL CLEAN EXIT.
    ft_memset(cmd, 0, sizeof(t_cmd));
    cmd->n_type = N_EXEC;
    return (t_cmd *)cmd;
}

t_cmd*  parse_exec(t_cmd *cmd, t_list *cur_tkn_pos)
{
    t_execcmd   *cmd;
    t_cmd       *ret;

    ret = bld_exec_nd();


    //CALL REDIR


    while (cur_tkn_pos) //RUN WHILE I DONT FIND A PIPE
    {
        //In the first iteration its the same pos from parse_pipe() loop.
        cur_tkn_pos = cur_tkn_pos->next;
        //CHECK REDIR INSIDE.
    }

    //SET THE LAST ARGV AS 0?

    
    //HERE WORK WITH THIS NODE AND CALL REDIR IF NEEDED.
    ret->curr_tkn_pos = cur_tkn_pos;
    return (ret);
}

/*Start calling parse_exec to build the very first node of the tree.
Then move forward into the other tree nodes.*/
t_cmd*  parse_pipe(t_shell *sh)
{
    t_cmd   *cmd;
    t_list  *tkn_lst;

    (void)sh;
    
    tkn_lst = sh->token_lst;
	while (tkn_lst)
	{
		//tkn_cont = tkn_lst->content;
		cmd = parse_exec(cmd, tkn_lst);
		tkn_lst = tkn_lst->next;
	}

    return (cmd);
}

/*Runs each token node and builds the tree.*/
void    parsing_tree(t_shell *sh)
{
    (void)sh;
    /*
    1) Call Pipe Constructor
    2) Call EXEC
    3) Call REDIR*/
    sh->cmd = parse_pipe(sh);
}

/*
*/