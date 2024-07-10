/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:42:00 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/13 18:39:05 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_shell *sh, char *str)
{
	char	*new_token;
	char	*expanded;
	int		i;

	new_token = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (check_exp(str[i]))
				expanded = expansion(sh, str, &i);
			else
				expanded = ft_strjoin("$", get_word(str, &i));
		}
		else
			expanded = get_word(str, &i);
		new_token = ft_strjoin_mod(new_token, expanded);
		if (expanded)
			free(expanded);
	}
	free(str);
	return (new_token);
}

char	*generate_temp_filename(t_shell *sh, char *file, int nbr)
{
	char	*filename;
	char	*file_aux;
	char	*num;
	int		random_number;

	filename = NULL;
	random_number = (sh->pid + (int)file[0] + ft_strlen(file)) * nbr;
	file_aux = ft_strdup(".tmp_heredoc_");
	num = ft_itoa(random_number);
	filename = ft_strjoin(file_aux, num);
	free(file_aux);
	free(num);
	return (filename);
}

char	*create_temp_file(t_shell *sh, char *file, int i)
{
	char	*filename;
	int		fd;

	filename = generate_temp_filename(sh, file, i);
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(filename);
		return (NULL);
	}
	close(fd);
	return (filename);
}

void	append_doc_to_file(char *filename, char *content)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return ;
	write(fd, content, ft_strlen(content));
	write(fd, "\n", 1);
	close(fd);
}
