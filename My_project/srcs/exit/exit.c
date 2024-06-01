/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:10:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/01 13:53:49 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_token_content(void *content)
{
	t_token	*curr_cont;

	curr_cont = (t_token *)(content);
	if (!curr_cont)
		return ;
	if (curr_cont->value)
		free(curr_cont->value);
	free(curr_cont);
}

void	free_env_list(t_list **env_lst)
{
	ft_lstclear(env_lst, free_lst_content);
}

void	free_token_list(t_list **token_list)
{
	ft_lstclear(token_list, free_token_content);
}

void	clear_exit(t_shell *sh, int status)
{
	int i;

	i = 0;
	if (!sh)
		exit(EXIT_FAILURE);
	free_env_list(&sh->env_lst);
	free_token_list(&sh->token_lst);
	free(sh->index);
	/*if (sh->cmd)
		free_tree(sh->cmd);*/
	if (sh->paths)
	{
		while (sh->paths[i])
		{
			free(sh->paths[i]);
			i++;
		}
		free(sh->paths);
	}
	rl_clear_history();
	exit(status);
}
