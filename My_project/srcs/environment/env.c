/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:38:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/13 15:38:29 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_env	*ft_lstnew_env(char *key, char *value, bool visible)
{
	t_env	*temp;

	temp = ft_calloc(1, sizeof(t_env));
	if (!temp)
		return (NULL);
	temp->key = key;
	temp->value = value;
	temp->visible = visible;
	temp->next = NULL;
	return (temp);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*last;

	if (!*env)
		*env = new;
	else
	{
		last = ft_lstlast_env(*env);
		if (last)
			last->next = new;
	}
}*/

char	*get_value(char *env_var, int pos)
{
	char	*value;
	int		size;

	size = (int)ft_strlen(&env_var[pos + 1]);
	value = ft_calloc(1, sizeof(char) * (size));
	if (!value)
		return (NULL);
	ft_strlcpy(value, &env_var[pos + 1], size + 1);
	return (value);
}

char	*get_key(char *env_var, int pos)
{
	char	*key;

	key = ft_calloc(1, sizeof(char) * (pos + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, &env_var[0], pos + 1);
	return (key);
}

/*Put the environment variables in a linked list.*/
void	fill_env(t_shell *sh, char **env_var)
{
	char	*sep;
	int		pos;
	t_env	*node_content;
	t_list	*new_node;
	int		i = 0;
	t_list	*env_lst;


	pos = 0;
	env_lst = ft_calloc(1, sizeof(t_list *));	
	
	node_content = ft_calloc(1, sizeof(t_env));
	sh->env_lst = env_lst;
	printf("IGNORE fill_env()%s IGNORE\n", sh->str);
	while (*env_var)
	{
		sep = ft_strchr(*env_var, '=');
		if (sep)
		{
			pos = (int)(sep - *env_var);
			node_content->key = get_key(*env_var, pos);
			node_content->value = get_value(*env_var, pos);
			node_content->visible = true;
			node_content->id = i;
			if (node_content->key && node_content->value)
			{
				new_node = ft_lstnew(node_content);
				ft_lstadd_back(&sh->env_lst, new_node);
				printf("ID HEAD: %d | ID: %d\n", ((t_env *)(sh->env_lst->content))->id,\
						((t_env *)(new_node->content))->id);
				/*printf("%s %s %d\n", ((t_env *)(sh->env_lst->content))->key,\
				((t_env *)(sh->env_lst->content))->value, ((t_env *)(sh->env_lst->content))->visible);*/
				
				/*printf("%s %s %d\n", ((t_env *)(new_node->content))->key,\
				((t_env *)(new_node->content))->value, ((t_env *)(new_node->content))->visible);*/
			}

		}
		i++;
		env_var++;
	}
		//printf("ID HEAD: %d | ID: %d\n", ((t_env *)(head->content))->id, ((t_env *)(new_node->content))->id);
		/*printf("%s %s %d\n", ((t_env *)(sh->env_lst->content))->key,\
				((t_env *)(sh->env_lst->content))->value, ((t_env *)(sh->env_lst->content))->visible);*/
		//sh->env_lst = sh->env_lst->next;
}
