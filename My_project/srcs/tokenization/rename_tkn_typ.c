/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename_tkn_typ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:22:14 by uviana-a          #+#    #+#             */
/*   Updated: 2024/05/04 15:22:17 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	chk_typ(int type, int inf, int sup)
{
	return (type >= inf && type <= sup);
}

/*Set the rules of type replacement.*/
void	repl_tkn_typ(t_token *tkn_src, t_token *tkn_des)
{
	int	new_type;

	if (tkn_src->type == GREATER)
		new_type = OUTFILE;
	else if (tkn_src->type == LESSER)
		new_type = INFILE;
	else if (tkn_src->type == D_GREATER)
		new_type = APPEND;
	else if (tkn_src->type == D_LESSER)
		new_type = HEREDOC;
	else
		return ;
	tkn_des->type = new_type;
}

/*Set the process of type replacement*/
void	def_new_tkn_typ(t_list *tmp)
{
	t_token	*tkn_src;
	t_token	*tkn_des;

	tkn_src = NULL;
	tkn_des = NULL;
	if (chk_typ(((t_token *)(tmp->next->content))->type, WORD, WORD))
	{
		tkn_src = tmp->content;
		tkn_des = tmp->next->content;
	}
	else if (chk_typ(((t_token *)(tmp->next->content))->type, \
			E_SPACE, E_SPACE))
	{
		tkn_src = tmp->content;
		tmp = tmp->next;
		tkn_des = tmp->next->content;
	}
	repl_tkn_typ(tkn_src, tkn_des);
}

/*Changes the type of the next node if the current node is an operator type.*/
void	review_tkn_typ(t_list *tkn_lst)
{
	t_list	*tmp;
	t_token	*tkn_cont;

	tmp = tkn_lst;
	while (tmp)
	{
		tkn_cont = tmp->content;
		if (chk_typ(tkn_cont->type, GREATER, D_LESSER))
			def_new_tkn_typ(tmp);
		tmp = tmp->next;
	}
}
