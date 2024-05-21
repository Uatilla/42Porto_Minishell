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

/*CONSTRUCTORS*/
t_cmd   *execcmd(t_shell *sh)
{
    t_execcmd   *cmd;

    (void)sh;
    cmd = malloc(sizeof(t_execcmd));
    if (!cmd)
        clear_exit(sh, 1); //CLEAN RECURSIVELY
    ft_memset(cmd, 0, sizeof(t_execcmd));
    /*allocate memory for the argv*/
    cmd->n_type = N_EXEC;
    return (t_cmd *)cmd;
        
}

t_cmd*  parse_exec(t_shell *sh, t_list *tkn_pos)
{
    t_cmd   *ret;
    t_token *tkn_cont;

    (void)sh;

    ret = execcmd(sh);
    /*SET THE EXEC NODE*/
    //(void)ret;



    while (tkn_pos)
    {
        ret->curr_tkn_pos = tkn_pos;
        tkn_cont = ret->curr_tkn_pos->content;
        if (tkn_cont->type == WORD)
        {
            printf("CMD: %s \n", tkn_cont->value);
        }
        else if (tkn_cont->type == INFILE || tkn_cont->type == OUTFILE 
                || tkn_cont->type == APPEND)
        {
            printf("REDIR: %s\n", tkn_cont->value);
        }
        else if (tkn_cont->type == PIPE)
            break ;
        tkn_pos = tkn_pos->next;
    }    
    return (ret);
}

/*Start calling parse_exec to build the very first node of the tree.
Then move forward into the other tree nodes.*/
t_cmd*  parse_pipe(t_shell *sh, t_list *tkn_pos)
{
    t_cmd   *cmd;

    (void)sh;
    cmd = parse_exec(sh, tkn_pos);
    tkn_pos = cmd->curr_tkn_pos;
    if (cmd && tkn_pos && ((t_token *)(tkn_pos->content))->type == PIPE)
    {
        tkn_pos = tkn_pos->next;
        cmd = parse_pipe(sh, tkn_pos);
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
    sh->cmd = parse_pipe(sh, sh->token_lst);
}

/*
*/