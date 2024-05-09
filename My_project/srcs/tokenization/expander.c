/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/09 21:59:46 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_expander_node(t_list **list, t_list *node)
{
	t_list *prev;
	t_list *curr;

	if (list == NULL || node == NULL)
		return ;

	// If the node to be removed is the head of the list
	if (*list == node)
	{

			*list = (*list)->next;
			ft_lstdelone(node, &free_token_content);
			return ;
	}
	prev = *list;
	curr = (*list)->next;

	// Find the previous node of the node to be removed
	while (curr != NULL && curr != node)
	{
		prev = curr;
		curr = curr->next;
	}
	// If the node to be removed is found
	if (curr == node)
	{
		prev->next = curr->next;
		ft_lstdelone(curr, &free_token_content);
	}
}

// void	remove_node(t_list **lst, t_list *node_to_remove)
// {
// 	t_list	*current;
// 	t_list	*prev;

// 	prev = NULL;
// 	current = *lst;
// 	if (!lst || !*lst || !node_to_remove)
// 		return ;
// 	if (current == node_to_remove)
// 	{
// 		*lst = current->next;
// 		ft_lstdelone(current, &free_token_content);
// 		return ;
// 	}
// 	while (current && current != node_to_remove)
// 	{
// 		prev = current;
// 		current = current->next;
// 	}
// 	if (current == node_to_remove)
// 	{
// 		prev->next = current->next;
// 		ft_lstdelone(current, &free_token_content);
// 	}
// }

void	expander(t_list **token)
{
	t_list *tmp;
	t_list *tmp_prev;

	tmp = *token;
	while (tmp != NULL)
	{
		if (!ft_strncmp(((t_token *)tmp->content)->value, "$", 2) && tmp->next != NULL)
		{
			if (((t_token *)tmp->next->content)->type != E_SPACE && (((t_token *)tmp->next->content)->state == IN_DQUOTES || ((t_token *)tmp->next->content)->state == IN_SQUOTES))
			{
				tmp_prev = tmp;
				tmp = tmp->next;
				((t_token *)tmp->content)->type = ((t_token *)tmp_prev->content)->type;
				remove_expander_node(token, tmp_prev);
			}
		}
		tmp = tmp->next;
	}
}