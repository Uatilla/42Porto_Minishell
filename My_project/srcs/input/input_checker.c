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

/*Look for unclosed quotes, and returns the close quote position.*/
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

/*Validates if the current search is the first pos
in the input string.*/
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

/*Do the validation of syntax analysing quotes, 
and operators.*/
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
		if (is_a_pipe(input[i]) && ((ch_fst(input, '|') || \
			only_white(input, i + 1))))
			return (prt_stx_error("|", false));
		else
		{
			if (!spc_char_check(input, i))
				return (false);
		}
	}
	return (true);
}
