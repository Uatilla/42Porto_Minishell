/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:06:41 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/14 18:21:44 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_last_word(t_list *token_lst)
{
	t_list	*current;
	t_list	*last;
	bool	found_first_word;

	current = token_lst;
	last = NULL;
	found_first_word = false;
	while (current)
	{
		if (get(current)->type == WORD)
		{
			if (!found_first_word)
			{
				found_first_word = true;
				last = current;
			}
			else
				last = current;
		}
		current = current->next;
	}
	return (last);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node_content;

	node_content = ft_calloc(1, sizeof(t_env));
	node_content->key = ft_strdup(key);
	if (value)
		node_content->value = ft_strdup(value);
	else
		node_content->value = NULL;
	node_content->visible = true;
	return (node_content);
}

void	update_env_list(t_shell *sh, t_env *node_content)
{
	t_list	*to_remove;

	to_remove = find_env_node(sh->env_lst, node_content->key);
	if (to_remove)
		remove_env_node(&sh->env_lst, to_remove);
	ft_lstadd_back(&sh->env_lst, ft_lstnew(node_content));
	if (sh->envp)
		free_path(sh->envp);
	sh->envp = list_to_array(sh, sh->env_lst, 2);
}

int	env(t_shell *sh, t_execcmd *cmd)
{
	if (!sh->env_lst)
		return (1);
	if (cmd->argv[1])
	{
		if (cmd->argv[1][0] == '-')
			custom_error("env: illegal option ", cmd->argv[1], "\nusage: env (with no arguments)", 1);
		else
			custom_error("env: ", cmd->argv[1], "No such file or directory", 127);
	}
	else if (cmd)
		print_env(sh);
	return (g_signo);
}
