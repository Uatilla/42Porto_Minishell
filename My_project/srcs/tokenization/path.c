/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:14:55 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/03 20:47:16 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_pipe(__attribute__((unused)) t_shell *sh, char *input)
{
	char	*ret;
	char	*join;
	char	*temp;

	join = ft_strdup(input);
	while (1)
	{
		ret = readline("> ");
		if (!ret)
			return (free(join), NULL);// Handle EOF (Ctrl+D)
		ret = ft_strtrim_mod(ret, " \t");
		temp = ft_strdup(join);
		join = ft_strjoin_mod(join, ret);
		free(temp);
		free(ret);
		join = ft_strtrim_mod(join, " \t");
		if (join[ft_strlen(join) - 1] != '|')
			break ;
		if (join[ft_strlen(join) - 1] == '|'
			&& join[ft_strlen(join) - 2] == '|')
			return (free(join), custom_error(NULL, SYNTAX_PIPE, 2), NULL);
	}
	return (join);
}

char	*get_line(t_shell *sh)
{
	char	*input;
	char	*trimmed_input;
	char	*ret;

	ret = NULL;
	input = readline(PROMPT);
	if (!input || !*input)
	{
		free(input);
		sh_loop(sh);
	}
	if (!ft_strncmp(input, "exit", 5))
	{
		free(input);
		clear_exit(sh, 1);
	}
	if (!ft_strcmp(input, "clear"))
	{
		free(input);
		system("clear");
		reinit_shell(sh);
		sh_loop(sh);
	}
	trimmed_input = ft_strtrim(input, "\t ");
	if (trimmed_input[ft_strlen(trimmed_input) - 1] == '|')
	{
		ret = open_pipe(sh, trimmed_input);
		free(trimmed_input);
	}
	else
		ret = trimmed_input;
	free(input);
	add_history(ret);
	return (ret);
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
	char	*path_aux;

	sh->envp = list_to_array(sh, sh->env_lst, 2);
	path_aux = get_path_aux(sh->envp);
	if (path_aux)
		sh->paths = ft_split(path_aux, ':');
	free(path_aux);
}
