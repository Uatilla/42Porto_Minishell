/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:10:11 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 20:20:03 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_node(t_list **list, t_list *node)
{
	t_list	*prev;
	t_list	*curr;

	if (list == NULL || node == NULL)
		return ;
	if (*list == node)
	{
		*list = (*list)->next;
		ft_lstdelone(node, &free_env_content);
		return ;
	}
	prev = *list;
	curr = (*list)->next;
	while (curr != NULL && curr != node)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == node)
	{
		prev->next = curr->next;
		ft_lstdelone(curr, &free_env_content);
	}
}

t_list	*find_env_node(t_list *list, char *key)
{
	t_list	*tmp;
	t_env	*content;

	tmp = list;
	while (tmp)
	{
		content = tmp->content;
		if (!ft_strcmp(content->key, key))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	att_env(t_shell *sh, char *key, char *new_value)
{
	t_list	*last;
	t_env	*node_content;
	t_list	*to_remove;

	last = find_last_word(sh->token_lst);
	if (ft_strcmp(key, "_") == 0)
	{
		if (!last)
		{
			to_remove = find_env_node(sh->env_lst, "_");
			if (to_remove)
				((t_env *)to_remove->content)->visible = false;
			return ;
		}
		node_content = create_env_node("_", get(last)->value);
	}
	else
	{
		node_content = create_env_node(key, new_value);
	}
	update_env_list(sh, node_content);
	get_paths(sh);
}
