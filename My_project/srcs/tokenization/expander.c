/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 17:52:37 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_list *env_list, char *token)
{
	t_list	*env;
	char	*expansion;
	char	*key;

	env = env_list;
	expansion = ft_strdup("");
	while (env)
	{
		key = ((t_env *)env->content)->key;
		if (!ft_strcmp(token, key) && ((t_env *)env->content)->visible)
		{
			free(expansion);
			expansion = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	return (expansion);
}

char	*expansion(t_shell *sh, char *str, int *i)
{
	char	*key;
	char	*new_token;
	int		start;

	if (ft_isnumber(str[*i]) || search_char(OPERATORS_EX, str[*i]))
	{
		new_token = simple_expand(sh, str[*i]);
		(*i)++;
		return (new_token);
	}
	start = *i;
	while (isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	key = ft_substr(str, start, (*i) - start);
	new_token = get_env(sh->env_lst, key);
	free(key);
	return (new_token);
}

void	expand_general(t_shell *sh, t_list *tkn)
{
	int		i;
	char	*new_token;

	i = 0;
	new_token = NULL;
	if (get(tkn->next)->type >= 2 && get(tkn->next)->type <= 6)
		return ;
	free(get(tkn)->value);
	if (get(tkn->next)->state != GENERAL)
	{
		get(tkn)->value = ft_strdup(get(tkn->next)->value);
		get(tkn)->state = get(tkn->next)->state;
	}
	else if (get(tkn)->type == HEREDOC)
		get(tkn)->value = ft_strjoin("$", get(tkn->next)->value);
	else
	{
		new_token = expansion(sh, get(tkn->next)->value, &i);
		get(tkn)->value = ft_strjoin(new_token, &get(tkn->next)->value[i]);
	}
	if (new_token)
		free(new_token);
	remove_node(&sh->token_lst, tkn->next);
}

void	expand_quotes(t_shell *sh, t_list *token)
{
	char	*new_token;
	char	*expanded;
	int		i;

	new_token = ft_strdup("");
	i = 0;
	while (get(token)->value[i])
	{
		if (get(token)->value[i] == '$')
		{
			i++;
			if (check_exp(get(token)->value[i]))
				expanded = expansion(sh, get(token)->value, &i);
			else
				expanded = ft_strjoin("$", get_word(get(token)->value, &i));
		}
		else
			expanded = get_word(get(token)->value, &i);
		new_token = ft_strjoin_mod(new_token, expanded);
		if (expanded)
			free(expanded);
	}
	free(get(token)->value);
	get(token)->value = new_token;
}
