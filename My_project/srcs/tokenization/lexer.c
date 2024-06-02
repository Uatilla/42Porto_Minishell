/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/02 19:21:24 by lebarbos         ###   ########.fr       */
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

// Função principal refatorada
void	review_tkn_list(t_list **tkn)
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
		tmp = tmp->next;
	}
}
char	*expand_heredoc(t_shell *sh, char *str)
{
	char	*new_token;
	char	*expanded;
	int		i;

	new_token = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (check_exp(str[i]))
				expanded = expansion(sh->env_lst, str, &i);
			else
				expanded = ft_strjoin("$", get_word(str, &i));
		}
		else
			expanded = get_word(str, &i);
		new_token = ft_strjoin_mod(new_token, expanded);
		if (expanded)
			free(expanded);
	}
	free(str);
	return (new_token);
}

void	get_doc(t_shell *sh, t_list *tmp)
{
	char	*ret;

	ret = NULL;
	while (1)
	{
		ret = readline("> ");
		if (!get(tmp)->not_expand)
			ret = expand_heredoc(sh, ret);
		if (!ft_strcmp(ret, get(tmp)->value))
		{
			free(ret);
			break ;
		}
		// append doc
		free(ret);
	}
}

void	handle_heredoc(t_shell *sh, t_list *tkns)
{
	t_list	*tmp;
	char	*ret;

	tmp = tkns;
	while (tmp)
	{
		if (get(tmp)->type == HEREDOC)
		{
			// Create future infile -> return an file name
			// get _doc -> appends the DOC to the file
			//  -> change the token value to the file name and change token 
		}
		tmp = tmp->next;
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
	handle_heredoc(sh, sh->token_lst);
}
