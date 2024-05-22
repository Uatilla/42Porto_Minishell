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
t_cmd   *execcmd(t_shell *sh, t_list *tkn_pos)
{
    t_execcmd   *cmd;

    (void)sh;
    cmd = malloc(sizeof(t_execcmd));
    if (!cmd)
        clear_exit(sh, 1); 
        /*Clean all elements of the tree:
            *argv[]: From ft_strdup() fill_execcmd()
            cmd->argv[]: From the execcmd().
            Exec Node = cmd: From execcmd().
            Redir Node = cmd: From redircmd().
            Pipe Node = cmd: From pipecmd().
            */
    ft_memset(cmd, 0, sizeof(t_execcmd));
    cmd->n_type = N_EXEC;
    cmd->curr_tkn_pos = tkn_pos;
    cmd->argv = malloc(1024 * sizeof(char *));//QTY.
    if (!cmd->argv)
        clear_exit(sh, 1);
    ft_memset(cmd->argv, 0, sizeof(char *));
    return (t_cmd *)cmd;
        
}

void    fill_execcmd(t_shell *sh, t_execcmd *cmd, char *arg)
{
    int     argc;

    argc = 0;
    while (cmd->argv[argc])
        argc++;
    printf("CMD[%d]: %s \n", argc, arg);
    cmd->argv[argc] = ft_strdup(arg);
    if (!cmd->argv[argc])
        clear_exit(sh, 1);

}

t_cmd   *redircmd(t_shell *sh, t_cmd *subcmd, char *file, int mode, int fd)
{
    t_redircmd  *cmd;

    cmd = malloc(sizeof(t_redircmd));
    if (!cmd)
        clear_exit(sh, 1);
    ft_memset(cmd, 0, sizeof(t_redircmd));
    cmd->n_type = N_REDIR;
    cmd->cmd = subcmd;
    cmd->file = file;
    cmd->mode = mode;
    cmd->fd = fd;
    cmd->curr_tkn_pos = subcmd->curr_tkn_pos;
    return (t_cmd *)cmd;
}

t_cmd   *parse_redir(t_shell *sh, t_cmd *cmd)
{
    t_token *tkn_cont;
    int     redir_type;
    
    tkn_cont = cmd->curr_tkn_pos->content;
    redir_type = tkn_cont->type;
    if (redir_type == INFILE)
        cmd = redircmd(sh, cmd, tkn_cont->value, O_RDONLY, 0);
    else if (redir_type == OUTFILE)
        cmd = redircmd(sh, cmd, tkn_cont->value, O_WRONLY|O_CREAT|O_TRUNC, 1);
    else if (redir_type == APPEND)
        cmd = redircmd(sh, cmd, tkn_cont->value, O_WRONLY|O_CREAT, 1);
    else if (redir_type == HEREDOC)
        printf("HEREDOC\n");
    return (cmd);
}

t_cmd   *parse_exec(t_shell *sh, t_list *tkn_pos)
{
    t_cmd       *ret;
    t_execcmd   *ex_cmd;
    t_token     *tkn_cont;

    (void)sh;
    ret = execcmd(sh, tkn_pos);
    ex_cmd = (t_execcmd *)ret;
    while (ret->curr_tkn_pos)
    {
        tkn_cont = ret->curr_tkn_pos->content;
        if (tkn_cont->type == WORD)
            fill_execcmd(sh, ex_cmd, tkn_cont->value);
        else if (tkn_cont->type == INFILE || tkn_cont->type == OUTFILE 
                || tkn_cont->type == APPEND)
        {
            ret = parse_redir(sh, ret);
            printf("REDIR: %s\n",((t_redircmd *)(ret))->file);
        }
        else if (tkn_cont->type == PIPE)
            break ;
        ret->curr_tkn_pos = ret->curr_tkn_pos->next;
    }
    return (ret);
}

/*t_cmd   *parse_exec(t_shell *sh, t_list *tkn_pos)
{
    t_cmd       *ret;
    t_execcmd   *ex_cmd;
    t_token     *tkn_cont;

    (void)sh;
    ret = execcmd(sh);
    ex_cmd = (t_execcmd *)ret;
    while (tkn_pos)
    {
        ret->curr_tkn_pos = tkn_pos;
        tkn_cont = ret->curr_tkn_pos->content;
        if (tkn_cont->type == WORD)
            fill_execcmd(sh, ex_cmd, tkn_cont->value);
        else if (tkn_cont->type == INFILE || tkn_cont->type == OUTFILE 
                || tkn_cont->type == APPEND)
        {
            //ret = parse_redir(sh, ret, tkn_pos);
            printf("REDIR: %s\n", tkn_cont->value);
        }
        else if (tkn_cont->type == PIPE)
            break ;
        tkn_pos = tkn_pos->next;
    }
    return (ret);
}*/

t_cmd   *pipecmd(t_shell *sh, t_cmd *left, t_cmd *right)
{
    t_pipecmd   *cmd;

    cmd = malloc(sizeof(t_pipecmd));
    if (!cmd)
        clear_exit(sh, 1);
    ft_memset(cmd, 0, sizeof(t_pipecmd));
    cmd->n_type = N_PIPE;
    cmd->left = left;
    cmd->right = right;
    return (t_cmd *)cmd;
}

/*Start calling parse_exec to build the very first node of the tree.
Then move forward into the other tree nodes.*/
t_cmd   *parse_pipe(t_shell *sh, t_list *tkn_pos)
{
    t_cmd   *cmd;
    //int     i;

    (void)sh;
    cmd = parse_exec(sh, tkn_pos);
    tkn_pos = cmd->curr_tkn_pos;
    //i = 0;
    /*while (((t_execcmd *)(cmd))->argv[i])
    {
        printf("Argv[%d]: %s\n", i, ((t_execcmd *)(cmd))->argv[i]);
        i++;
    }*/
    if (cmd && tkn_pos && ((t_token *)(tkn_pos->content))->type == PIPE)
    {
        tkn_pos = tkn_pos->next;
        //cmd = parse_pipe(sh, tkn_pos); WORKING
        cmd = pipecmd(sh, cmd, parse_pipe(sh, tkn_pos));

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
    printf("NT: %d\n", sh->cmd->n_type);
}

/*
*/