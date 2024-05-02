/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:13:59 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/02 11:14:50 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '>' && !search_char(">", token[1]))
		return (GREATER);
	else if (token[0] == '<' && !search_char("<", token[1]))
		return (LESSER);
	else if (token[0] == '>' && token[1] == '>')
		return (D_GREATER);
	else if (token[0] == '<' && token[1] == '<')
		return (D_LESSER);
	else if (token[0] == ' ')
		return (E_SPACE);
	else
		return (WORD);
}

void	get_token_state(t_token *token)
{
	char	*new_value;
	char	cmp;

	new_value = NULL;
	if (token->value[0] == '\'' || token->value[0] == '\"')
	{		
		if (token->value[0] == '\"')
			token->state = IN_DQUOTES;
		else if (token->value[0] == '\'')
			token->state = IN_SQUOTES;
		cmp = token->value[0];
		new_value = ft_strtrim(token->value, &cmp);
		free(token->value);
		token->value = new_value;
	}
	else
		token->state = GENERAL;
}

void	end_word(t_shell *sh, char *input)
{
	sh->index->end = sh->index->start;
	if (input[sh->index->end] == '\"' || input[sh->index->end] == '\'')
		search_quote(input, &sh->index->end, input[sh->index->end]);
	else
		search_word(input, &sh->index->end);
}

void	fill_token_lst(t_shell *sh, char *input)
{
	t_token	*node_content;

	while (input[sh->index->start])
	{
		node_content = ft_calloc(1, sizeof(t_token));
		if (!node_content)
			clear_exit(sh, 1);
		if (ft_iswhitespace(input[sh->index->start]))
		{
			node_content->value = ft_strdup(" ");
			while (ft_iswhitespace(input[sh->index->start]))
				sh->index->start++;
		}
		else
		{
			end_word(sh, input);
			node_content->value = ft_substr(input, sh->index->start,
					sh->index->end - sh->index->start);
			sh->index->start = sh->index->end;
		}
		node_content->type = get_token_type(node_content->value);
		get_token_state(node_content);
		ft_lstadd_back(&sh->token_lst, ft_lstnew(node_content));
		node_content->pos = sh->index->pos++;
	}
}
