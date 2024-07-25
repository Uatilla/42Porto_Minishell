/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:42:37 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 17:15:43 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_command_location(t_shell *sh, char *command, char *path_i)
{
	char	*path_aux;
	char	*path_command;

	path_command = NULL;
	path_aux = ft_strjoin(path_i, "/");
	path_command = ft_strjoin(path_aux, command);
	free(path_aux);
	if (!path_command)
		clear_exit(sh, 1);
	if (access(path_command, F_OK) == 0)
		return (path_command);
	free(path_command);
	return (NULL);
}

char	*relative_path(t_shell *sh, char *command)
{
	char	*path_command;
	int		i;

	i = 0;
	path_command = NULL;
	if (!sh->paths)
		return (NULL);
	else
	{
		while (sh->paths[i])
		{
			path_command = ft_check_command_location(sh, command, sh->paths[i]);
			if (path_command != NULL)
				return (path_command);
			i++;
		}
	}
	return (path_command);
}

char	*find_path(t_shell *sh, char *command)
{
	char	*path_command;
	int		i;

	i = -1;
	i++;
	path_command = NULL;
	if (!command || !*command)
		return (NULL);
	if (command[0] == '/' || (ft_strncmp(command, "./", 2) == 0))
		path_command = ft_strdup(command);
	else if (ft_strnstr(command, ".sh", ft_strlen(command))
		&& ft_strchr(command, '/'))
		path_command = ft_strdup(command);
	else
		path_command = relative_path(sh, command);
	return (path_command);
}
