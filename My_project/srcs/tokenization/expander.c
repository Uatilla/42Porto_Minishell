/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:48:12 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/07 20:02:57 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_list *token)
{
	t_list *tmp;
	char new_value;

	tmp = token;
	new_value = NULL;
	while (token)
	{
		if (((t_token *)tmp->content)->value[0] == '$')
		{
			if (((t_token *)tmp->content)->value[1] == '\0')
			{
				if (((t_token *)tmp->next->content)->value[0] == ' ' || !((t_token *)tmp->next->content))
					continue;
			}
		}
		
	}
}