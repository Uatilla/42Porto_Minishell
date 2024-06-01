/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/01 20:04:28 by lebarbos         ###   ########.fr       */
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
			get(tmp)->value = ft_strjoin_mod(get(tmp)->value,
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

void get_last_token(__attribute_maybe_unused__ t_list *tkn_list )
{
	char	*new_token;

	new_token = readline("> ");
	
}

// Função principal refatorada
void	review_tkn_list(t_list **tkn)
{
	t_list	*tmp;
	int		typee;
	int		i;
	int		size_list;

	i = 1;
	size_list = ft_lstsize(*tkn);
	printf("\n\nLISTSIZE: %d\n\n", size_list);

	tmp = *tkn;
	while (tmp)
	{
		typee = get(tmp)->type;
		if (tmp && i == (size_list) && get(tmp)->type == PIPE)
		{
			printf("HEREEE\n\n");
			get_last_token(*tkn);
		}
		if (typee >= 7)
		{
			transform_nodes(tmp->next, typee);
			if (typee == HEREDOC)
				handle_heredoc(tmp);
			tmp = tmp->next;
		}
		else
		{
			tmp = tmp->next;
		}
		i++;
	}
}

void	lexer(t_shell *sh, char *input)
{
	fill_token_lst(sh, input);
	review_tkn_typ(sh->token_lst);
	review_tkn_list(&sh->token_lst);
	expander(sh, &sh->token_lst);
	clean_tokenlist(&sh->token_lst);
	// print_tokens(sh);
}
