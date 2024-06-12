/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:10:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/12 10:21:35 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_error(char *file, char *message, int error)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("bash: ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	g_signo = error;
}

void	free_env_content(void *content)
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
	if (curr_cont->type == HEREDOC)
		unlink(curr_cont->value);
	if (curr_cont->value)
		free(curr_cont->value);
	free(curr_cont);
}

void	free_env_list(t_list **env_lst)
{
	ft_lstclear(env_lst, free_env_content);
}

void	free_token_list(t_list **token_list)
{
	ft_lstclear(token_list, free_token_content);
}
