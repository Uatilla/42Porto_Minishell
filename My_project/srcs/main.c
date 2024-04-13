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
	/*0) Set t_shell struct as 0.*/
	ft_bzero(sh, sizeof(t_shell));
	/*1) Put each *env into the structure
	Remember to set the visibility var as true*/
	fill_env(sh, env_var);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	init_shell(&sh, envp);
	while (sh.env->next)
	{
		printf("%s %s %d\n", sh.env->key, sh.env->value, sh.env->visible);
		sh.env = sh.env->next;
	}
	printf("IGNORE main(): %d \t %s IGNORE\n", argc, argv[1]);
	return (0);
}
