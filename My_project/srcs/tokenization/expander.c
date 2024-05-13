/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/13 20:38:21 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_expander_node(t_list **list, t_list *node)
{
	t_list *prev;
	t_list *curr;

	if (list == NULL || node == NULL)
		return ;
	if (*list == node)
	{

			*list = (*list)->next;
			ft_lstdelone(node, &free_token_content);
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

void	expand_node(t_shell *sh, t_list *expander, char *key)
{
	t_list *env;

	env = sh->env_lst;
	while(env)
	{
		if (!ft_strncmp(key, ((t_env *)env->content)->key, ft_strlen(key)) && ((t_token *)expander->content)->type != HEREDOC)
		{
			free(((t_token *)expander->content)->value);
			((t_token *)expander->content)->value = ft_strdup(((t_env *)env->content)->value);
			printf("%s\n", ((t_env *)env->content)->value);
			return ;
		}
		env = env->next;
	}
}

char	*get_env(t_list *env_list, t_token *token)
{
	t_list *env;
	char	*expansion;
	char	*new_token;
	char	*new_key;
	char	*new_sub;
	int		i;

	env = env_list;
	expansion = NULL;
	new_token = NULL;
	new_key = NULL;
	i = 0;
	if (token->value[i] == '0' || token->value[i] == '?' || token->value[i] == '$')
	{
		expansion = ft_strdup("lalala");
		i++;
	}
	else
	{
		while (ft_isalnum(token->value[i]))
			i++;
		new_key = ft_substr(token->value, 0, i);
		while(env)
		{
			if (!ft_strncmp(new_key, ((t_env *)env->content)->key,
				ft_strlen(token->value)))
				expansion = ft_strdup(((t_env *)env->content)->value);
			else
				expansion = ft_strdup(new_key);
			env = env->next;
		}
		if (expansion == NULL)
			expansion = ft_strdup("\0");
	}
	new_sub = ft_substr(token->value, i, ft_strlen(token->value) - i);
	new_token = ft_strjoin(expansion, new_sub);
	free(new_sub);
	free(new_key);
	free(expansion);
	return (new_token);
}

void	simple_expand(t_list *token_node)
{
	char *new_token;
	t_token	*token_content;

	token_content = token_node->content;
	new_token = NULL;
	if (token_content->value[1] == '$')
		new_token = ft_itoa(getpid());
	else if (token_content->value[1] == '?')
		new_token = ft_itoa(g_signo);
	else if (token_content->value[1] == '0')
		new_token = ft_strdup("bash");
	free(((t_token *)token_node->content)->value);
	((t_token *)token_node->content)->value = new_token;
}

t_list	*expand_aux(t_shell *sh, t_list *xtoken)
{
	free(((t_token *)xtoken->content)->value);
	if (((t_token *)xtoken->next->content)->state != GENERAL || ((t_token *)xtoken->content)->type == HEREDOC)
	{
		((t_token *)xtoken->content)->value = ft_strdup(((t_token *)xtoken->next->content)->value);
		((t_token *)xtoken->content)->state = (((t_token *)xtoken->next->content)->state);
	}
	else
	{
		((t_token *)xtoken->content)->value = get_env(sh->env_lst, (t_token *)xtoken->next->content);
	}
	remove_expander_node(&sh->token_lst, xtoken->next);
	return (xtoken);
}

char	*get_env2(t_shell *sh,  char *key, int *index)
{
	char *new_key;
	t_list *env;
	char	*expansion;
	int		start;

	env = sh->env_lst;
	expansion = NULL;
	printf("%s\n", key);
	(*index)++;
	start = *index;
	while(ft_isalnum(key[(*index)]))
		(*index)++;
	new_key = ft_substr(key, start, *index - 1);
	while (env)
	{
		if (!ft_strncmp(new_key, ((t_env *)env->content)->key,
			ft_strlen(new_key)))
			expansion = ft_strdup(((t_env *)env->content)->value);
		env = env->next;
	}
	free(new_key);
	return (expansion);
}

void	expand_inside_word(t_shell *sh, t_list *tokens)
{
	t_token	*token_content;
	char	*new_token_value;
	char	*expansion;
	int index_key;
	char	*key;

	index_key = 0;
	new_token_value = ""; // Initialize new_token_value to an empty string
	while(tokens)
	{
		index_key = 0;
		token_content = tokens->content;
		key = ft_strdup(token_content->value);
		if (token_content->state == IN_DQUOTES && ft_strlen(token_content->value) >= 2)
		{
			free(token_content->value);
			while(key[index_key])
			{
				{
					if (key[index_key] == '$' && token_content->type != HEREDOC)
						expansion = get_env2(sh, key, &index_key);
					else
					{
						expansion = ft_substr(key, index_key, 1);
						index_key++;
					}
					new_token_value = ft_strjoin(new_token_value, expansion);
					free(expansion);
				}
			}
			token_content->value = ft_strdup(new_token_value);
			free(new_token_value);
		}
		free(key);
		tokens = tokens->next;
	}
}

void	expander(t_shell *sh, t_list **tokens)
{
	t_list *tmp;
	t_list *to_exclude;

	tmp = *tokens;
	while (tmp)
	{
		if(((t_token *)tmp->content)->value[0] == '$' && ((t_token *)tmp->content)->state == GENERAL)
		{
			// if (ft_strlen(((t_token *)tmp->content)->value) == 2)
			// 	simple_expand(tmp);
			if (tmp->next)
			{
				to_exclude = tmp;
				tmp = expand_aux(sh, to_exclude);
			}
		}
		else if (((t_token *)tmp->content)->type != E_SPACE && ((t_token *)tmp->content)->state != IN_SQUOTES)
			expand_inside_word(sh, tmp);
		tmp = tmp->next;
	}
	tmp = *tokens;
}
