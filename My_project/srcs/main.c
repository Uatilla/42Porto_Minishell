/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/11 19:57:06 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_var(char **env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
		i++;
	return (i);
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	fill_env(sh, env_var);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;
	t_list	*temp_lst;

	(void)argc;
	(void)argv;
	init_shell(&sh, envp);
	temp_lst = (sh.env_lst);
	while (temp_lst->next)
	{
		printf("%s %s %d\n", ((t_env *)(temp_lst->content))->key, \
			((t_env *)(temp_lst->content))->value, \
				((t_env *)(temp_lst->content))->visible);
		temp_lst = temp_lst->next;
	}
	printf("%s %s %d\n", ((t_env *)(temp_lst->content))->key, \
		((t_env *)(temp_lst->content))->value, \
			((t_env *)(temp_lst->content))->visible);
	clear_exit(&sh, 0);
	return (0);
}
