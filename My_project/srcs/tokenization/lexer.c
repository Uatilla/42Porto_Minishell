/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 15:04:45 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_home(t_shell *sh, t_list *tmp)
{
	char	*temp;
	char	*ret;
	char	*expand;

	expand = ft_strdup("");
	temp = get_env(sh->env_lst, "HOME");
	if (!ft_strcmp("~", get(tmp)->value))
		ret = ft_strdup(temp);
	else
	{
		expand = ft_strdup(&get(tmp)->value[1]);
		if (!expand)
			clear_exit(sh, 1);
		ret = ft_strjoin(temp, expand);
		if (!ret)
			clear_exit(sh, 1);
	}
	free(get(tmp)->value);
	free(expand);
	free(temp);
	return (ret);
}

bool	is_home(t_list *tmp)
{
	if (!ft_strcmp("~", get(tmp)->value) ||
		!ft_strncmp("~/", get(tmp)->value, 2))
		return (true);
	return (false);
		
}

void join_non_removable_nodes(t_list **tkns)
{
	t_list *tmp = *tkns;
	t_list *next;

	while (tmp && tmp->next)
	{
		if (!is_removable(get(tmp->next)->type) && !is_removable(get(tmp)->type)
			&& get(tmp)->type != PIPE && get(tmp->next)->type != PIPE)
		{
			next = tmp->next;
			get(tmp)->value = ft_strjoin_mod(get(tmp)->value, 
				get(tmp->next)->value);
			remove_node(tkns, next);
		}
		else
			tmp = tmp->next;
	}
}

void remove_removable_nodes_and_expand_home(__attribute_maybe_unused__ t_shell *sh, t_list **tkns)
{
	t_list *tmp = *tkns;
	t_list *next;

	while (tmp)
	{
		next = tmp->next;
		if (is_removable(get(tmp)->type))
			remove_node(tkns, tmp);
		// else if (is_home(tmp))
		// 	get(tmp)->value = expand_home(sh, tmp);
		tmp = next;
	}
}

void clean_tokenlist(t_shell *sh, t_list **tkns)
{
	join_non_removable_nodes(tkns);
	remove_removable_nodes_and_expand_home(sh, tkns);
}

void expand_general_tokens(t_shell *sh, t_list **tokens)
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
				// if (search_char(get(tmp)->value, " \t") && ((get(tmp)->type != INFILE && get(tmp)->type != OUTFILE && get(tmp)->type != APPEND)))
				// {
					
				// }
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

void expand_quote_tokens(t_shell *sh, t_list **tokens)
{
	t_list *tmp = *tokens;
	t_list *next;

	while (tmp)
	{
		next = tmp->next;
		if (get(tmp)->state == IN_DQUOTES)
		{
			if (get(tmp)->type != HEREDOC && get(tmp)->value[0])
			{
				expand_quotes(sh, tmp);
				if (!*get(tmp)->value && ((get(tmp)->type != INFILE && get(tmp)->type != OUTFILE && get(tmp)->type != APPEND)))
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
		else if(typee == PIPE)
			sh->nbr_pipes++;
		tmp = tmp->next;
	}
}

void	lexer(t_shell *sh, char *input)
{
	fill_token_lst(sh, input);
	review_tkn_typ(sh->token_lst);
	review_tkn_list(sh, &sh->token_lst);
	expander(sh, &sh->token_lst);
	// print_tokens(sh);
	clean_tokenlist(sh, &sh->token_lst);
	handle_heredoc(sh, &sh->token_lst);
	if (sh->nbr_pipes == 0)
		builtins_parent(sh);
	// att_env(sh, "_", NULL);
}
