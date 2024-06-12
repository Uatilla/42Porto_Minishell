/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:25:33 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 18:21:00 by lebarbos         ###   ########.fr       */
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

void	join_non_removable_nodes(t_shell *sh, t_list **tkns)
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
			if (!get(tmp)->value)
				clear_exit(sh, 1);
			remove_node(tkns, next);
		}
		else
			tmp = tmp->next;
	}
}

void	remove_removable_nodes(t_shell *sh, t_list **tkns)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *tkns;
	while (tmp)
	{
		next = tmp->next;
		if (is_removable(get(tmp)->type))
			remove_node(tkns, tmp);
		else if (is_home(tmp))
			get(tmp)->value = expand_home(sh, tmp);
		tmp = next;
	}
}
