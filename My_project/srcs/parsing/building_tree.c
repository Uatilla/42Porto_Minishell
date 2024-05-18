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

t_cmd   *build_exec_nd(void)
{
    t_execcmd   *cmd;


    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL); //IF THIS RETURNS AN ERROR, SHOULD CALL CLEAN EXIT.
    ft_memset(cmd, 0, sizeof(t_cmd));
    cmd->n_type = N_EXEC;
    return (t_cmd *)cmd;
}

t_cmd*  build_redir_nd(t_cmd *subcmd, char *file, int mode, int fd)
{
    t_redircmd  *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL); //IF THIS RETURNS AN ERROR, SHOULD CALL CLEAN EXIT.
    ft_memset(cmd, 0, sizeof(t_cmd));
    cmd->n_type = N_REDIR;
    cmd->cmd = subcmd;
    cmd->file = file;
    cmd->mode = mode;
    cmd->fd = fd;
    return ((t_cmd *)cmd);
}

t_cmd*  parse_redir(t_cmd *cmd, t_list *pos_tkn_lst)
{
    t_token *tkn_cont;
    int redir_type;

    tkn_cont = ((t_token *)(pos_tkn_lst->content));
    redir_type = tkn_cont->type;
    if (redir_type == INFILE)
    {
        cmd = build_redir_nd(cmd, tkn_cont->value, O_RDONLY, 0);
        cmd->curr_tkn_pos = pos_tkn_lst;
    }
    return (cmd);//IF THE THE CUR TKN IS NOT A REDIR, STAY IN THE SAME TKN POS.
}

t_cmd*  parse_exec(t_list *pos_tkn_lst)
{
    t_execcmd   *cmd;
    t_cmd       *ret;
    t_token     *tkn_cont;
    int         argc;

    
    ret = build_exec_nd(); //Build the blank exec structure.
    ret->curr_tkn_pos = pos_tkn_lst;
    cmd = (t_execcmd *)ret;
    argc = 0;

    //loop infinito
    while (pos_tkn_lst) //CONTINUE RUNNING TKN_LST AND RUN WHILE I DONT FIND A PIPE
    {
        tkn_cont = ((t_token *)pos_tkn_lst->content);
        if (tkn_cont->type == WORD)
        {
            printf("%s\n", tkn_cont->value);
            //cmd->argv[argc] = ft_strdup(tkn_cont->value); // REMEMBER TO FREE
            argc++;
        }
        else if (tkn_cont->type == INFILE || tkn_cont->type == OUTFILE || tkn_cont->type == APPEND)
        {
            ret = parse_redir(ret, pos_tkn_lst);
            pos_tkn_lst = ret->curr_tkn_pos;
        }
        else if (tkn_cont->type == PIPE)
            break;
        pos_tkn_lst = pos_tkn_lst->next;
    }
    //cmd->argv[argc] = ft_calloc(1, sizeof(char *));
    ret->curr_tkn_pos = pos_tkn_lst;
    return (ret);
}

/*Start calling parse_exec to build the very first node of the tree.
Then move forward into the other tree nodes.*/
t_cmd*  parse_pipe(t_shell *sh)
{
    t_cmd   *cmd;
    t_list  *pos_tkn_lst;

    (void)sh;
    
    pos_tkn_lst = sh->token_lst;
	while (pos_tkn_lst)
	{
		//tkn_cont = tkn_lst->content;
		cmd = parse_exec(pos_tkn_lst); //SEND THE CURR TOKEN LIST POS.
		pos_tkn_lst = cmd->curr_tkn_pos; //UPDATE THE CUR TKN POS FROM CMD STRUCTURE.
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