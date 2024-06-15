/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:06:07 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/15 13:49:25 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	ft_bzero(sh->index, sizeof(t_index));
	sh->nbr_pipes = 0;
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	sh->index = malloc(sizeof(t_index));
	if (!sh->index)
	{
		write(1, "Malloc error!", 14);
		clear_exit(sh, 1);
	}
	ft_bzero(sh->index, sizeof(t_index));
	if (!env_var[0])
		init_empty_env(sh);
	if (env_var)
	{
		fill_env(sh, env_var);
		sh->envp = list_to_array(sh, sh->env_lst, 2);
		get_paths(sh);
	}
}

int	fork1(t_shell *sh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed\n");
		clear_exit(sh, 1);
	}
	sh->pid = pid;
	return (pid);
}
