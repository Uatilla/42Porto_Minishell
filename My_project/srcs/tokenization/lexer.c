/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/19 16:50:20 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tokenlist(t_list **tkns)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *tkns;
	while (tmp && tmp->next)
	{
		if (!is_removable(get(tmp->next)->type)
			&& !is_removable(get(tmp)->type))
		{
			next = tmp->next;
			get(tmp)->value = ft_strjoin(get(tmp)->value,
				get(tmp->next)->value);
			remove_node(tkns, next);
		}
		else
			tmp = tmp->next;
	}
	tmp = *tkns;
	while (tmp)
	{
		next = tmp->next;
		if (is_removable(get(tmp)->type))
			remove_node(tkns, tmp);
		tmp = next;
	}
}

void	expander(t_shell *sh, t_list **tokens)
{
	t_list	*tmp;
	t_list	*to_exclude;

	tmp = *tokens;
	while (tmp)
	{
		if (get(tmp)->value[0] == '$' && get(tmp)->state == GENERAL
			&& tmp->next)
		{
			if (get(tmp->next)->type != E_SPACE)
			{
				to_exclude = tmp;
				expand_general(sh, to_exclude);
			}
		}
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (get(tmp)->state == IN_DQUOTES)
			if (get(tmp)->type != HEREDOC)
				expand_quotes(sh, tmp);
		tmp = tmp->next;
	}
}

void	review_tkn_list(t_list **tkn)
{
	t_list	*tmp;
	t_list	*nxt;

	tmp = *tkn;
	while (tmp)
	{
		nxt = tmp->next;
		if (ft_strcmp(get(tmp)->value, "") == 0
			&& !is_removable(get(nxt)->type))
		{
			get(nxt)->type = get(tmp)->type;
			remove_node(tkn, tmp);// Remove o nó atual
		}
		tmp = nxt;// Avança para o próximo nó
	}
}

void	lexer(t_shell *sh, char *input)
{
	fill_token_lst(sh, input); //tokens without state;
	review_tkn_typ(sh->token_lst); // set state
	review_tkn_list(&sh->token_lst);
	expander(sh, &sh->token_lst);
	clean_tokenlist(&sh->token_lst); // join and clean spaces
	print_tokens(sh); // just print
}
