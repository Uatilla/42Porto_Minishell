/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 19:50:55 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tokenlist(t_shell *sh, t_list **tkns)
{
	join_non_removable_nodes(sh, tkns);
	remove_removable_nodes(sh, tkns);
}

// Função principal refatorada
void	review_tkn_list(t_shell *sh, t_list **tkn)
{
	t_list	*tmp;
	int		typee;

	tmp = *tkn;
	while (tmp)
	{
		typee = get(tmp)->type;
		if (typee >= 7)
		{
			transform_nodes(tmp->next, typee);
			if (typee == HEREDOC)
				set_heredoc_type(tmp);
		}
		else if (typee == PIPE)
			sh->nbr_pipes++;
		tmp = tmp->next;
	}
}

void	lexer(t_shell *sh, char *input)
{
	fill_token_lst(sh, input);
	review_tkn_typ(sh->token_lst);
	review_tkn_list(sh, &sh->token_lst);
	expand_general_tokens(sh, &sh->token_lst);
	expand_quote_tokens(sh, &sh->token_lst);
	clean_tokenlist(sh, &sh->token_lst);
	handle_heredoc(sh, &sh->token_lst);
	if (sh->nbr_pipes == 0)
		att_env(sh, "_", NULL);
}
