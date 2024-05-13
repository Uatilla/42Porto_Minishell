/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:20:33 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/13 20:23:05 by lebarbos         ###   ########.fr       */
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
	if (input[*end] && search_char("<>|$", input[*end])
		&& !search_char("\"\'", input[*end]))
	{
		if (input[*end] == '$')
		{
			(*end)++;
			// if (input[*end] == '$' || (input[*end] >= '0' && 
			// input[*end] <= '9') || input[*end] == '?')
			// 	(*end)++;
			return ;
		}
		while (input[*end] && search_char("<>|", input[*end])
			&& !search_char("\"\'", input[*end]) && input[*end] != '$')
			(*end)++;
		return ;
	}
	if (input[*end] && search_char("\"\'", input[*end]))
		search_quote(input, end, input[*end]);
	else
	{
		while (input[*end] && !search_char("\"\'", input[*end])
			&& !search_char("<>|$", input[*end])
			&& !ft_iswhitespace(input[*end]))
			(*end)++;
	}
}
