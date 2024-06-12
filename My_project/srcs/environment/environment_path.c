/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:01:11 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/12 19:01:13 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	get_paths(t_shell *sh)
{
	char	*path_aux;

	if (sh->paths)
		free_path(sh->paths);
	path_aux = get_path_aux(sh->envp);
	if (path_aux)
		sh->paths = ft_split(path_aux, ':');
	free(path_aux);
}
