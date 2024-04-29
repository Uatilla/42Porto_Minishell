/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:32:43 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/18 20:32:47 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	prt_stx_error(char *error, bool exit)
{
	printf("bash: syntax error near unexpected token `%s'\n", error);
	return (exit);
}

bool	check_bigger(char *input, int i)
{
	if ((only_white(input, i + 1)) || is_a_pipe(input [i + 1]) || \
		(is_a_bigger(input[i + 1]) && only_white(input, i + 2)))
		return (prt_stx_error("newline", false));
	else if (is_a_bigger(input [i + 1]) && is_a_bigger(input [i + 2]))
		return (prt_stx_error(">", false));
	else if (is_a_smaller(input [i + 1]))
		return (prt_stx_error("<", false));
	else if (((is_a_bigger(input[i + 1]) && is_a_pipe(input [i + 2]))))
		return (prt_stx_error("|", false));
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
	return (true);
}

bool	spc_char_check(char *input, int i)
{
	if (is_a_bigger(input[i]))
		return (check_bigger(input, i));
	else if (is_a_smaller(input[i]))
		return (check_smaller(input, i));
	else if (is_a_pipe(input[i]))
	{
		if (is_a_bigger(input [i + 1]) || is_a_smaller(input [i + 1]))
				return (prt_stx_error("|", false));
	}
	else if (ft_strchr(OUTOFSCOPE, input[i]))
		return (prt_stx_error("Out of Scope:", false));
	return (true);
}

int	search_c_quote(char *input, int i, char search)
{
	while (input[++i])
	{
		if (input[i] == search)
			return (i);
	}
	printf("bash: syntax error quote unclosed `%c'\n", search);
	return (i);
}

bool	ch_fst(char *input, char search)
{
	int		i;
	bool	fst_wrd;

	i = 0;
	fst_wrd = true;
	while (input[i])
	{
		if (input[i] == search && fst_wrd == true)
			return (true);
		else if (!ft_iswhitespace(input[i]))
			return (false);
		i++;
	}
	return (false);
}

bool	sintax_validation(char *input)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = search_c_quote(input, i, input[i]);
			if (!input[i])
				return (false);
		}
		/*if ((is_a_pipe(input[i])) && (ch_fst(input, '|') || \
			only_white(input, i + 1)))
			return (prt_stx_error("|", false));*/
		/*ESSA FUNCAO ABAIXO PRECISA SER REVISTA, PORQUE ELA
		PULA A POSICAO NA SAIDA E NO WHILE PRINCIPAL, IGNORANDO UM
		CHAR DO INPUT A SER ANALISADO	*/
		if (is_a_pipe(input[i]))
		{
			if ((ch_fst(input, '|') || only_white(input, i + 1)))
				return (prt_stx_error("|", false));
			while (ft_iswhitespace(input[++i]))
				continue ;
			if (is_a_pipe(input[i]))
				return (prt_stx_error("|", false));
		}
		else
		{
			if (!spc_char_check(input, i))
				return (false);
		}
	}
	return (true);
}
