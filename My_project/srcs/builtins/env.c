/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:06:41 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/07 19:46:11 by lebarbos         ###   ########.fr       */
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

void	att_env(t_shell *sh, t_execcmd *cmd)
{
	t_env	*node_content;
	// t_env	*test_content;
	t_list	*to_remove;
	int		size;

	node_content = ft_calloc(1, sizeof(t_env));
	size = ft_lstsize(sh->env_lst);
	to_remove = find_env_node(sh->env_lst, "_");
	if (to_remove)
	{
		// test_content = to_remove->content;
		// printf("env to remove: %s\n", test_content->value);
		remove_env_node(&sh->env_lst, to_remove);
	}
	node_content->key = ft_strdup("_");
	node_content->value = ft_strdup(cmd->argv[0]);
	node_content->visible = true;
	free_array(sh->envp, size);
	ft_lstadd_back(&sh->env_lst, ft_lstnew(node_content));
	sh->envp = list_to_array(sh, sh->env_lst, 2);
	ft_putstr_fd(sh->envp[2], 2);
	ft_putstr_fd("\n", 2);
	print_env(sh);
	print_arrays(sh->envp);
}

int	env(t_shell *sh, __attribute_maybe_unused__ t_execcmd *cmd)
{
	// ft_putstr_fd("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n", 2);
	print_arrays(sh->envp);
	return (0);
}
