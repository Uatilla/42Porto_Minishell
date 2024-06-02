/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:25:33 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/02 17:53:27 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_removable(int type)
{
	if (type >= 2 && type <= 6)
		return (1);
	return (0);
}

void	transform_nodes(t_list *start, int type)
{
	while (start && get(start)->type == 0)
	{
		get(start)->type = type;
		start = start->next;
	}
}

void	set_heredoc_type(t_list *start)
{
	t_list	*inner_tmp;
	t_list	*heredoc_start;

	inner_tmp = start;
	while (inner_tmp && get(inner_tmp)->type != E_SPACE)
	{
		if (get(inner_tmp)->state == IN_DQUOTES
			|| get(inner_tmp)->state == IN_SQUOTES)
		{
			heredoc_start = start;
			while (heredoc_start && get(heredoc_start)->type != E_SPACE)
			{
				get(heredoc_start)->not_expand = true;
				heredoc_start = heredoc_start->next;
			}
			break ;
		}
		inner_tmp = inner_tmp->next;
	}
}
