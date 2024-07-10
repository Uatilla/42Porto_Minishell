/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:10:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/16 12:28:32 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_home(t_shell *sh, t_list *tmp)
{
	char	*temp;
	char	*ret;
	char	*expand;

	expand = NULL;
	temp = get_env(sh->env_lst, "~");
	if (!ft_strcmp("~", get(tmp)->value))
		ret = ft_strdup(temp);
	else
	{
		expand = ft_strdup(&get(tmp)->value[1]);
		if (!expand)
			clear_exit(sh, 1);
		ret = ft_strjoin(temp, expand);
		if (!ret)
			clear_exit(sh, 1);
	}
	free(get(tmp)->value);
	if (expand)
		free(expand);
	free(temp);
	return (ret);
}

bool	is_home(t_list *tmp)
{
	if (!ft_strcmp("~", get(tmp)->value)
		|| !ft_strncmp("~/", get(tmp)->value, 2))
		return (true);
	return (false);
}
