/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:52:00 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 10:52:12 by lebarbos         ###   ########.fr       */
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
		if (!ft_strcmp(key, "HOME") && !ft_strcmp("~", token))
		{
			free(expansion);
			expansion = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		else if (!ft_strcmp(token, key) && ((t_env *)env->content)->visible)
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

void	handle_non_general_state(t_list *tkn)
{
	free(get(tkn)->value);
	get(tkn)->value = ft_strdup(get(tkn->next)->value);
	get(tkn)->state = get(tkn->next)->state;
}

void	handle_heredoc_type(t_list *tkn)
{
	free(get(tkn)->value);
	get(tkn)->value = ft_strjoin("$", get(tkn->next)->value);
}
