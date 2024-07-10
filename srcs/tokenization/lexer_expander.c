/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:05:52 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/12 19:05:56 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expd_general_home(t_shell *sh, t_list *tmp)
{
	get(tmp)->value = expand_home(sh, tmp);
}

void	expd_general_tkns_aux(t_shell *sh, t_list **tokens, t_list *tmp, \
	t_list *to_exclude)
{
	t_list	*next;

	while (tmp)
	{
		if (is_home(tmp) && get(tmp)->state == GENERAL)
			expd_general_home(sh, tmp);
		else if (get(tmp)->value[0] == '$' && get(tmp)->state == GENERAL
			&& tmp->next)
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

void	expand_general_tokens(t_shell *sh, t_list **tokens)
{
	t_list	*tmp;
	t_list	*to_exclude;

	tmp = *tokens;
	to_exclude = NULL;
	expd_general_tkns_aux(sh, tokens, tmp, to_exclude);
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

void	expander(t_shell *sh, t_list **tokens)
{
	expand_general_tokens(sh, tokens);
	expand_quote_tokens(sh, tokens);
}
