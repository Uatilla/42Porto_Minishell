/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 21:00:38 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_word_type(t_shell *sh, t_list *tkn, int *i)
{
	char	*new_token;

	new_token = expansion(sh, get(tkn->next)->value, i);
	new_token = ft_strjoin_mod(new_token, &get(tkn->next)->value[*i]);
	return (new_token);
}

void	update_token_value(t_list *tkn, char *new_token)
{
	if (new_token)
	{
		free(get(tkn)->value);
		get(tkn)->value = ft_strdup(new_token);
		free(new_token);
	}
}

void	expand_general(t_shell *sh, t_list *tkn)
{
	int		i;
	char	*new_token;

	new_token = NULL;
	i = 0;
	if (get(tkn->next)->type >= 2 && get(tkn->next)->type <= 6)
		return ;
	if (get(tkn->next)->state != GENERAL)
		handle_non_general_state(tkn);
	else if (get(tkn)->type == HEREDOC)
		handle_heredoc_type(tkn);
	else if (get(tkn)->type != WORD)
	{
		new_token = handle_word_type(sh, tkn, &i);
		if (!new_token || !*new_token)
		{
			if (!*new_token)
				free(new_token);
			return ;
		}
	}
	else
		new_token = handle_word_type(sh, tkn, &i);
	update_token_value(tkn, new_token);
	remove_node(&sh->token_lst, tkn->next);
}

void	expand_quotes(t_shell *sh, t_list *token)
{
	char	*new_token;
	char	*expanded;
	int		i;

	new_token = ft_strdup("");
	i = 0;
	while (get(token)->value[i])
	{
		if (get(token)->value[i] == '$')
		{
			i++;
			if (check_exp(get(token)->value[i]))
				expanded = expansion(sh, get(token)->value, &i);
			else
				expanded = ft_strjoin("$", get_word(get(token)->value, &i));
		}
		else
			expanded = get_word(get(token)->value, &i);
		new_token = ft_strjoin_mod(new_token, expanded);
		if (expanded)
			free(expanded);
	}
	free(get(token)->value);
	get(token)->value = new_token;
}
