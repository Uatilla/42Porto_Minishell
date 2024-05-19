/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:38 by lebarbos         ###   ########.fr       */
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
	while (tmp && tmp->next)
	{
		nxt = tmp->next;
		if (ft_strcmp(get(tmp)->value, "") == 0
			&& !is_removable(get(nxt)->type))
		{
			get(nxt)->type = get(tmp)->type;
			remove_node(tkn, tmp);// Remove o nó atual
		}
		else if (get(tmp)->type == HEREDOC)
        {
            char *joined_value = strdup(get(tmp)->value);
            t_list *to_remove = nxt;
            while (to_remove && !is_removable(get(to_remove)->type))
            {
                char *new_joined_value = ft_strjoin(joined_value, get(to_remove)->value);
                free(joined_value); // Liberar a string anterior
                joined_value = new_joined_value;
                to_remove = to_remove->next;
            }
            free(get(tmp)->value); // Liberar o valor antigo
            get(tmp)->value = joined_value; // Atualizar com o novo valor unido

            // Remover todos os nós subsequentes até encontrar um tipo removível
            while (nxt && nxt != to_remove)
            {
                t_list *next_nxt = nxt->next;
                remove_node(tkn, nxt);
                nxt = next_nxt;
            }
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
