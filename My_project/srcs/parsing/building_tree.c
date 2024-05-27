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

/*Select the right parameters to build the redir node and calls it.*/
t_cmd	*parse_redir(t_shell *sh, t_cmd *cmd)
{
	t_token	*tkn_cont;
	int		redir_type;

	tkn_cont = cmd->curr_tkn_pos->content;
	redir_type = tkn_cont->type;
	if (redir_type == INFILE)
		cmd = redircmd(cmd, tkn_cont->value, O_RDONLY, 0);
	else if (redir_type == OUTFILE)
		cmd = redircmd(cmd, tkn_cont->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (redir_type == APPEND)
		cmd = redircmd(cmd, tkn_cont->value, O_WRONLY | O_CREAT, 1);
	else if (redir_type == HEREDOC)
		printf("HEREDOC\n");
	if (!cmd)
		clear_exit(sh, 1);
	return (cmd);
}

/*Build the first tree node (exec), run the token list updating 
the args from exec or updating the pointer to a redir.
Stops when a pipe was found.*/
t_cmd	*parse_exec(t_shell *sh, t_list *tkn_pos)
{
	t_cmd		*ret;
	t_execcmd	*ex_cmd;
	t_token		*tkn_cont;

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
			printf("REDIR: %s\n", ((t_redircmd *)(ret))->file);
		}
		else if (tkn_cont->type == PIPE)
			break ;
		ret->curr_tkn_pos = ret->curr_tkn_pos->next;
	}
	return (ret);
}

/*Start calling parse_exec to build the very first node of the tree.
Then move forward into the pipe (if exists).*/
t_cmd	*parse_pipe(t_shell *sh, t_list *tkn_pos)
{
	t_cmd	*cmd;

	(void)sh;
	cmd = parse_exec(sh, tkn_pos);
	tkn_pos = cmd->curr_tkn_pos;
	if (cmd && tkn_pos && ((t_token *)(tkn_pos->content))->type == PIPE)
	{
		tkn_pos = tkn_pos->next;
		cmd = pipecmd(sh, cmd, parse_pipe(sh, tkn_pos));
	}
	return (cmd);
}

/*Start the tree by the exec node.*/
void	parsing_tree(t_shell *sh)
{
	(void)sh;
	sh->cmd = parse_pipe(sh, sh->token_lst);
}
