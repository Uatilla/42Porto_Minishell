/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:09:42 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/15 19:09:47 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_content(void *content)
{
	t_env	*curr_cont;

	curr_cont = (t_env *)(content);
	if (!curr_cont)
		return ;
	free(curr_cont->key);
	free(curr_cont->value);
	free(curr_cont);
}

void	free_env_list(t_list **env_lst)
{
	ft_lstclear(env_lst, free_lst_content);
}

void	clear_exit(t_shell *sh, int status)
{
	if (!sh)
		exit(EXIT_FAILURE);
	free_env_list(&sh->env_lst);
	exit(status);
}
