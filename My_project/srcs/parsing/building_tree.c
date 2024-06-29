/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:46:42 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/14 17:48:12 by lebarbos         ###   ########.fr       */
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
	if (redir_type == INFILE || redir_type == HEREDOC)
		cmd = redircmd(cmd, tkn_cont->value, O_RDONLY, 0);
	else if (redir_type == OUTFILE)
		cmd = redircmd(cmd, tkn_cont->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (redir_type == APPEND)
		cmd = redircmd(cmd, tkn_cont->value, O_WRONLY | O_CREAT | O_APPEND, 1);
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
	t_list		*tmp;
	t_execcmd	*ex_cmd;
	t_token		*tkn_cont;

	(void)sh;
	ret = execcmd(sh, tkn_pos);
	ex_cmd = (t_execcmd *)ret;
	tmp = ret->curr_tkn_pos;
	while (tmp)
	{
		tkn_cont = tmp->content;
		ret->curr_tkn_pos = tmp;
		if (tkn_cont->type == WORD)
			fill_execcmd(sh, ex_cmd, tkn_cont->value);
		else if (tkn_cont->type == INFILE || tkn_cont->type == OUTFILE
			|| tkn_cont->type == APPEND || tkn_cont->type == HEREDOC)
			ret = parse_redir(sh, ret);
		else if (tkn_cont->type == PIPE)
			break ;
		tmp = tmp->next;
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
	sh->cmd = parse_pipe(sh, sh->token_lst);
}

int	count_args(t_shell *sh, t_list *tkn_pos)
{
	t_token	*tkn_cont;
	int		count;

	count = 0;
	(void)sh;
	while (tkn_pos)
	{
		tkn_cont = (t_token *)tkn_pos->content;
		if (tkn_cont->type == WORD)
			count++;
		else if (tkn_cont->type == PIPE)
			break ;
		tkn_pos = tkn_pos->next;
	}
	return (count);
}
