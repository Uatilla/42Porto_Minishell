/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:13:59 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/01 16:32:35 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	search_quote(char *input, int *j, char c)
{
	(*j)++;
	while (input[*j] != c && input[*j])
		(*j)++;
	if (input[*j] == c)
		(*j)++;
}

void	search_word(char *input, int *end)
{
	if (input[*end] && search_char("<>|", input[*end])
		&& !search_char("\"\'", input[*end]))
	{
		while (input[*end] && search_char("<>|", input[*end])
			&& !search_char("\"\'", input[*end]))
			(*end)++;
		return ;
	}
	if (input[*end] && search_char("\"\'", input[*end]))
		search_quote(input, end, input[*end]);
	else
	{
		while (input[*end] && !search_char("\"\'", input[*end])
			&& !search_char("<>|", input[*end])
			&& !ft_iswhitespace(input[*end]))
			(*end)++;
	}
}

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

int	get_token_state(char *token)
{
	if (token[0] == '\"')
		return (IN_DQUOTES);
	else if (token[0] == '\'')
		return (IN_SQUOTES);
	else
		return (GENERAL);
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
		node_content->state = get_token_state(node_content->value);
		ft_lstadd_back(&sh->token_lst, ft_lstnew(node_content));
		node_content->pos = sh->index->pos++;
	}
}
