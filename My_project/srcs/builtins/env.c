/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:06:41 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/09 16:27:27 by lebarbos         ###   ########.fr       */
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

// void	att_env(t_shell *sh)
// {
// 	t_env	*node_content;
// 	t_list	*to_remove;
// 	t_list	*last;
// 	int		size;
// 	// int		i;

// 	// i = 0;
// 	last = sh->token_lst;
// 	while (last)
// 	{
// 		if (get(last)->type == WORD && last->next)
// 		{
// 			while (get(last->next)->type == WORD)
// 				last = last->next;
// 		}
// 		last = last->next;
// 	}
// 	node_content = ft_calloc(1, sizeof(t_env));
// 	size = ft_lstsize(sh->env_lst);
// 	to_remove = find_env_node(sh->env_lst, "_");
// 	if (to_remove)
// 		remove_env_node(&sh->env_lst, to_remove);
// 	node_content->key = ft_strdup("_");
// 	node_content->value = ft_strdup(get(last)->value);
// 	node_content->visible = true;
// 	free_array(sh->envp, size);
// 	ft_lstadd_back(&sh->env_lst, ft_lstnew(node_content));
// 	sh->envp = list_to_array(sh, sh->env_lst, 2);
// 	ft_putstr_fd(sh->envp[2], 2);
// 	ft_putstr_fd("\n", 2);
// 	print_env(sh);
// 	print_arrays(sh->envp);
// }

void update_or_add_env(t_shell *sh, char *key, char *value);
t_list *find_last_word(t_list *token_lst);
t_env *create_env_node(char *key, char *value);
void update_env_list(t_shell *sh, t_env *node_content);

void att_env(t_shell *sh, char *key, char *new_value)
{
    t_list *last;
    t_env *node_content;

    last = find_last_word(sh->token_lst);

    if (ft_strcmp(key, "_") == 0)
    {
        if (!last)
        {
            t_list *to_remove = find_env_node(sh->env_lst, "_");
            if (to_remove)
                ((t_env *)to_remove->content)->visible = false;
            return;
        }
        node_content = create_env_node("_", get(last)->value);
    }
    else
    {
        node_content = create_env_node(key, new_value);
    }
    update_env_list(sh, node_content);
}

t_list *find_last_word(t_list *token_lst)
{
    t_list *current = token_lst;
    t_list *last = NULL;
    bool found_first_word = false;

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
            {
                last = current;
            }
        }
        current = current->next;
    }
    return last;
}

t_env *create_env_node(char *key, char *value)
{
    t_env *node_content = ft_calloc(1, sizeof(t_env));
    node_content->key = ft_strdup(key);
    node_content->value = ft_strdup(value);
    node_content->visible = true;
    return node_content;
}

void update_env_list(t_shell *sh, t_env *node_content)
{
    t_list *to_remove = find_env_node(sh->env_lst, node_content->key);
    int size = ft_lstsize(sh->env_lst);

    if (to_remove)
        remove_env_node(&sh->env_lst, to_remove);

    free_array(sh->envp, size);
    ft_lstadd_back(&sh->env_lst, ft_lstnew(node_content));
    sh->envp = list_to_array(sh, sh->env_lst, 2);
}

// void att_env(t_shell *sh)
// {
//     t_env *node_content;
//     t_list *to_remove;
//     t_list *current;
//     t_list *last;
//     int size;
//     bool found_first_word = false;

//     current = sh->token_lst;
//     last = NULL;
//     while (current)
//     {
//         if (get(current)->type == WORD)
//         {
//             if (!found_first_word)
//             {
//                 found_first_word = true;
//                 last = current;
//             }
//             else
//                 last = current;
//         }
//         current = current->next;
//     }
//     to_remove = find_env_node(sh->env_lst, "_");
//     if (!last)
//     {
// 		((t_env *)to_remove->content)->visible = false;
//         return ;
//     }
//     node_content = ft_calloc(1, sizeof(t_env));
//     size = ft_lstsize(sh->env_lst);
//     if (to_remove)
//         remove_env_node(&sh->env_lst, to_remove);
//     node_content->key = ft_strdup("_");
//     node_content->value = ft_strdup(get(last)->value);
//     node_content->visible = true;
//     free_array(sh->envp, size);
//     ft_lstadd_back(&sh->env_lst, ft_lstnew(node_content));
//     sh->envp = list_to_array(sh, sh->env_lst, 2);
// }


int	env(t_shell *sh, t_execcmd *cmd)
{
	if (!sh->env_lst)
		return (1);
	if (cmd)
		print_env(sh);
	return (0);
}
