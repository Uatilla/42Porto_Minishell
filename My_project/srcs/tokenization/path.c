/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:14:55 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 16:33:58 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_and_join_input(char *join)
{
	char	*ret;
	char	*temp;

	ret = readline("> ");
	if (!ret)
		return (free(join), NULL);
	ret = ft_strtrim_mod(ret, " \t");
	temp = ft_strdup(join);
	join = ft_strjoin_mod(join, ret);
	free(temp);
	free(ret);
	join = ft_strtrim_mod(join, " \t");
	return (join);
}

char	*open_pipe(__attribute__((unused)) t_shell *sh, char *input)
{
	char	*join;

	join = ft_strdup(input);
	while (1)
	{
		join = read_and_join_input(join);
		if (!join)
			return (NULL);
		if (join[ft_strlen(join) - 1] != '|'
			|| join[ft_strlen(join) - 2] == '|')
			break ;
		if (!sintax_validation(join))
		{
			add_history(join);
			free(join);
			reinit_shell(sh);
			sh_loop(sh);
		}
	}
	return (join);
}

char	*handle_input(t_shell *sh, char *input)
{
	char	*trimmed_input;
	char	*ret;

	ret = NULL;
	trimmed_input = ft_strtrim(input, "\t ");
	if (!trimmed_input || !*trimmed_input || !sintax_validation(trimmed_input))
	{
		add_history(input);
		free(input);
		if (trimmed_input)
			free(trimmed_input);
		sh_loop(sh);
	}
	else if (trimmed_input[ft_strlen(trimmed_input) - 1] == '|')
		ret = open_pipe(sh, trimmed_input);
	else
		ret = ft_strdup(trimmed_input);
	free(input);
	if (trimmed_input)
		free(trimmed_input);
	return (ret);
}

char	*get_line(t_shell *sh)
{
	char	*input;

	input = readline(ROSE_2 PROMPT COLOR_RESET);
	if (!input)
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		clear_exit(sh, 0);
	}
	return (handle_input(sh, input));
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
