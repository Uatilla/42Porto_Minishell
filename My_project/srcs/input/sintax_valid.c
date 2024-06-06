/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:14:07 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/02 13:05:46 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_bigger(char *input, int i)
{
	if ((only_white(input, i + 1)) || (is_a_bigger(input[i + 1])
			&& only_white(input, i + 2)))
		return (prt_stx_error("newline", false));
	else if (is_a_bigger(input [i + 1]) && is_a_bigger(input [i + 2]))
		return (prt_stx_error(">", false));
	else if (is_a_smaller(input [i + 1]))
		return (prt_stx_error("<", false));
	else if (((is_a_bigger(input[i + 1]) && is_a_pipe(input [i + 2]))))
		return (prt_stx_error("|", false));
	else if (is_a_bigger(input [i + 1]) || ft_iswhitespace(input [i + 1]))
	{
		i++;
		while (ft_iswhitespace(input[++i]))
			continue ;
		if (ft_strchr(OPERATOR, input[i]))
			return (prt_stx_error("", false));
	}
	return (true);
}

bool	check_smaller(char *input, int i)
{
	if ((only_white(input, i + 1)) || (is_a_smaller(input[i + 1]) && \
	(is_a_smaller(input[i + 2]) || only_white(input, i + 2))))
		return (prt_stx_error("newline", false));
	else if (is_a_bigger(input [i + 1]) && only_white(input, i + 2))
		return (prt_stx_error("newline", false));
	else if (is_a_pipe(input[i + 1]) || ((is_a_smaller(input[i + 1]) && \
	is_a_pipe(input [i + 2]))))
		return (prt_stx_error("|", false));
	else if (is_a_smaller(input [i + 1]) || ft_iswhitespace(input [i + 1]))
	{
		i++;
		while (ft_iswhitespace(input[++i]))
			continue ;
		if (ft_strchr(OPERATOR, input[i]))
			return (prt_stx_error("", false));
	}
	return (true);
}

/*Validating operators sintax*/
bool	spc_char_check(char *input, int i)
{
	if (is_a_bigger(input[i]))
		return (check_bigger(input, i));
	else if (is_a_smaller(input[i]))
		return (check_smaller(input, i));
	else if (is_a_pipe(input[i]))
	{
		if ((is_a_bigger(input [i + 1]) || is_a_smaller(input [i + 1]))
			/* && (only_white(input, i + 2) || !input[i + 2]) */)
			return (prt_stx_error("|", false));
		while (ft_iswhitespace(input[++i]))
			continue ;
		if (is_a_pipe(input[i]))
			return (prt_stx_error("|", false));
	}
	else if (ft_strchr(OUTOFSCOPE, input[i]))
		return (prt_stx_error("Out of Scope:", false));
	return (true);
}
