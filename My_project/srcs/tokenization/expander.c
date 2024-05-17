/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/17 21:31:44 by lebarbos         ###   ########.fr       */
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

char	*get_env(t_list *env_list, char *token)
{
	t_list *env;
	char	*expansion;

	env = env_list;
	expansion = NULL;
	while(env)
	{
		if (!ft_strncmp(token, ((t_env *)env->content)->key,
			ft_strlen(token)))
		{
			expansion = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		else
			expansion = ft_strdup("");
		env = env->next;
	}
	return (expansion);
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

char	*expansion(t_list *env_list, char *str, int *i, t_token *token)
{
	char	*key;
	char	*new_token;
	int		start;
	
	new_token = "";
	if (token->state == IN_DQUOTES)
		(*i)++;
	start = *i;
	printf("String: %s\n\n", &str[*i]);
	if((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '$' || str[*(i)] == '?' || search_char(OPERATORS, str[*i]))
	{
		new_token = ft_strdup("lalala");
		(*i)++;
	}
	else 
	{
		while (isalnum(str[(*i)++]))
		{
			;
		}
		printf("\n\nNUMERO DE I DEPOIS: %d\n\n", *i);
		(*i)--;
		key = ft_substr(&str[start], 0, *i);
		printf("\n\nKEY: %s\n\n", key);
		new_token = get_env(env_list, key);
		free(key); // Add this line to free the allocated memory for key
	}
	return (new_token);
}

void	expand_general(t_shell *sh, t_list *xtoken)
{
	int i = 0; // Add this line to initialize the variable i
	char	*new_token;

	free(((t_token *)xtoken->content)->value);
	if (((t_token *)xtoken->next->content)->state != GENERAL || ((t_token *)xtoken->content)->type == HEREDOC)
	{
		((t_token *)xtoken->content)->value = ft_strdup(((t_token *)xtoken->next->content)->value);
		((t_token *)xtoken->content)->state = (((t_token *)xtoken->next->content)->state);
	}
	else
	{
		new_token = expansion(sh->env_lst, ((t_token *)xtoken->next->content)->value, &i, ((t_token *)xtoken->next->content)); // Pass the address of i to the expansion function	
		((t_token *)xtoken->content)->value = ft_strjoin(new_token, ft_strdup(&((t_token *)xtoken->next->content)->value[i]));
		free(new_token);
	}
	remove_expander_node(&sh->token_lst, xtoken->next);
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
						expansion = get_env(sh->env_lst, &key[index_key]);
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

void	expand_quotes(t_shell *sh, t_list *token)
{
	int		i;
	char	*token_str;
	char	*new_word;
	char	*new_token; 
	int	len;
	
	token_str = ft_strdup(((t_token *)token->content)->value);
	i = 0;
	len = 0;
	new_token = ft_strdup("");
	new_word = NULL;
	while (token_str[i] != '\0')
	{
		if (token_str[i] == '$' && token_str[i + 1] != '\0')
		{
			printf("NUMERO DE I: %d\n", i);
			new_word = expansion(sh->env_lst, token_str, &i, ((t_token *)token->content));
			new_token = ft_strjoin(new_token, new_word);
			free(new_word);

		}
		else
		{
			len = i;
			while (token_str[len] && isalnum(token_str[len]))
				len++;
			new_word = ft_substr(token_str, i, len);
			i=+len;
			new_token = ft_strjoin(new_token, new_word);
			free(new_word);
		}
		// i++;
	}
	free(((t_token *)token->content)->value);
	free(token_str);
	((t_token *)token->content)->value = new_token;
}

void	expander(t_shell *sh, t_list **tokens)
{
	t_list *tmp;
	t_list *to_exclude;

	tmp = *tokens;
	while (tmp)
	{
		if(((t_token *)tmp->content)->value[0] == '$' && ((t_token *)tmp->content)->state == GENERAL && (t_token *)tmp->next)
		{
			if (((t_token *)tmp->next->content)->type != E_SPACE)
			{
				to_exclude = tmp;
				expand_general(sh, to_exclude);
			}
		}
		else if (((t_token *)tmp->content)->type != E_SPACE && ((t_token *)tmp->content)->state != IN_SQUOTES)
			expand_quotes(sh, tmp);
		tmp = tmp->next;
	}
	tmp = *tokens;
}
