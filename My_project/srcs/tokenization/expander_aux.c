/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:05:30 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/20 12:16:29 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *str, int *i)
{
	char	*key;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	key = ft_substr(str, start, ((*i) - start));
	return (key);
}

int	check_exp(char key)
{
	if (isalnum(key) || search_char(OPERATORS_EX, key) || key == '_')
		return (1);
	return (0);
}

t_token	*get(t_list *token)
{
	return ((t_token *)token->content);
}

char	*simple_expand(char token)
{
	char	*new_token;

	new_token = "";
	if (token == '$')
		new_token = ft_itoa(getpid());
	else if (token == '?')
		new_token = ft_itoa(g_signo);
	else if (token == '0')
		new_token = ft_strdup("bash");
	return (new_token);
}

void	remove_node(t_list **list, t_list *node)
{
	t_list	*prev;
	t_list	*curr;

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
