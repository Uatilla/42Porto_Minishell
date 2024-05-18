/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/18 19:33:55 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get(t_list *token)
{
	void	*tken;

	tken = token->content;
	return (tken);
}

void	remove_expander_node(t_list **list, t_list *node)
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

char	*get_env(t_list *env_list, char *token)
{
	t_list	*env;
	char	*expansion;
	char	*key;

	env = env_list;
	expansion = "";
	while (env)
	{
		key = ((t_env *)env->content)->key;
		if (!ft_strncmp(token, key, ft_strlen(token)))
		{
			expansion = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	return (expansion);
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

char	*expansion(t_list *env_list, char *str, int *i)
{
	char	*key;
	char	*new_token;
	int		start;

	new_token = "";
	if ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '$' || str[*i] == '?') //|| search_char(OPERATORS, str[*i]))
	{
		new_token = simple_expand(str[*i]);
		(*i)++;
		return (new_token);
	}
	else
	{
		start = *i;
		if (isalnum(str[*i]))
			while (isalnum(str[*i]))
				(*i)++;
		else
			while (str[*i])
				(*i)++;
	}
	key = ft_substr(str, start, (*i) - start);
	new_token = get_env(env_list, key);
	free(key);
	return (new_token);
}

void	expand_general(t_shell *sh, t_list *tkn)
{
	int i;
	char	*new_token;
	
	i = 0;
	free(get(tkn)->value);
	if (get(tkn->next)->state != GENERAL)
	{
		get(tkn)->value = ft_strdup(get(tkn->next)->value);
		get(tkn)->state = (get(tkn->next)->state);
	}
	else if (get(tkn)->type == HEREDOC)
	{
		new_token = ft_strjoin("$", get(tkn->next)->value);
		get(tkn)->value = ft_strdup(new_token);
		free(new_token);
	}
	else
	{
		new_token = expansion(sh->env_lst, get(tkn->next)->value, &i);
		get(tkn)->value = ft_strjoin(new_token, &get(tkn->next)->value[i]);
		if (new_token && *new_token)
			free(new_token);
	}
	remove_expander_node(&sh->token_lst, tkn->next);
}

char	*get_word(char *str, int *i)
{
	char *key;
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$')
	{
		(*i)++;
	}
	key = ft_substr(str, start, ((*i) - start));
	return(key);
}

void expand_quotes(t_shell *sh, t_list *token) 
{
    char *new_token;
    char *expanded;
    int i;
	
	i = 0;
    new_token = ft_strdup("");
    while (get(token)->value[i]) 
	{
        if (get(token)->value[i] == '$')
		{
            i++;
            expanded = expansion(sh->env_lst, get(token)->value, &i);
        } 
		else 
            expanded = get_word(get(token)->value, &i);
        char *temp = new_token;
        new_token = ft_strjoin(new_token, expanded);
		if (expanded && *expanded)
			free(expanded);
        free(temp); 
    }
    free(get(token)->value); 
    get(token)->value = new_token;
}

void	expander(t_shell *sh, t_list **tokens)
{
	t_list *tmp;
	t_list *to_exclude;

	tmp = *tokens;
	while (tmp)
	{
		if(get(tmp)->value[0] == '$' && get(tmp)->state == GENERAL && tmp->next)
			if (get(tmp->next)->type != E_SPACE)
			{
				to_exclude = tmp;
				expand_general(sh, to_exclude);
			}
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (get(tmp)->state == IN_DQUOTES)
			if (get(tmp)->type != HEREDOC)
					expand_quotes(sh, tmp);
		tmp = tmp->next;
	}
}
