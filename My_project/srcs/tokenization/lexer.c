/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 10:22:00 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void join_non_removable_nodes(t_list **tkns)
{
	join_non_removable_nodes(sh, tkns);
	remove_removable_nodes(tkns);
}

void	expand_general_tokens(t_shell *sh, t_list **tokens)
{
	t_list *tmp = *tokens;
	t_list *to_exclude;
	t_list *next;

	while (tmp)
	{
		if (get(tmp)->value[0] == '$' && get(tmp)->state == GENERAL &&
			tmp->next)
		{
			if (get(tmp->next)->type != E_SPACE)
			{
				to_exclude = tmp;
				expand_general(sh, to_exclude);
				if ((!get(tmp)->value || !*get(tmp)->value))
				{
					next = tmp->next;
					remove_node(tokens, tmp);
					tmp = next;
					continue ;
				}
			}
		}
		tmp = tmp->next;
	}
}

void	expand_quote_tokens(t_shell *sh, t_list **tokens)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		if (get(tmp)->state == IN_DQUOTES)
		{
			if (get(tmp)->type != HEREDOC && get(tmp)->value[0])
			{
				expand_quotes(sh, tmp);
				if (!*get(tmp)->value && ((get(tmp)->type != INFILE
							&& get(tmp)->type != OUTFILE
							&&get(tmp)->type != APPEND)))
					remove_node(tokens, tmp);
			}
		}
		tmp = next;
	}
}

void expander(t_shell *sh, t_list **tokens)
{
	expand_general_tokens(sh, tokens);
	expand_quote_tokens(sh, tokens);
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
	handle_heredoc(sh, &sh->token_lst);
	if (sh->nbr_pipes == 0)
		builtins_parent(sh);
	att_env(sh, "_", NULL);
}
