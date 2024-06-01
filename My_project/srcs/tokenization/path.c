/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:14:55 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/01 19:09:21 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(t_shell *sh)
{
	char	*input;
	char	*trimmed_input;

	input = readline(PROMPT);
	if (!input || !*input)
		sh_loop(sh);
	add_history(input);
	if (!ft_strncmp(input, "exit", 5))
		clear_exit(sh, 1);
	if (!ft_strcmp(input, "clear"))
	{
		system("clear");
		reinit_shell(sh);
		sh_loop(sh);
	}
	trimmed_input = ft_strtrim(input, "\t ");
	free(input);
	return (trimmed_input);
}

char	*ft_get_path_aux(char **envp)
{
	int		i;
	char	*path_aux;

	i = 0;
	path_aux = NULL;
	if (!envp[0])
		path_aux = ft_strdup("/usr/bin:/bin");
	else
	{
		while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
			i++;
		if (envp[i] && envp[i][5] != '\0')
			path_aux = ft_strdup(envp[i] + 5);
	}
	return (path_aux);
}

char	*get_path_aux(char **envp)
{
	int		i;
	char	*path_aux;

	i = 0;
	path_aux = NULL;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (envp[i] && envp[i][5] != '\0')
		path_aux = ft_strdup(envp[i] + 5);
	return (path_aux);
}

void	get_paths(t_shell *sh)
{
	char	**envp;
	char	*path_aux;
	int		i;

	i = 0;
	envp = list_to_array(sh, sh->env_lst, 2);
	path_aux = get_path_aux(envp);
	if (path_aux)
		sh->paths = ft_split(path_aux, ':');
	while (envp[i])
		free(envp[i++]);
	free(envp);
	free(path_aux);
}
