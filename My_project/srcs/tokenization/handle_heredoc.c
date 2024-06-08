/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:40:49 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/08 23:29:42 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_temp_file(void)
{
	char	*filename;
	int		fd;

	filename = generate_temp_filename();
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

void	update_token_to_file(t_list *token, char *filename)
{
	if (get(token)->value)
		free(get(token)->value);
	get(token)->value = ft_strdup(filename);
}

char	*get_doc(t_shell *sh, t_list *tmp)
{
	char	*ret;
	char	*filename;

	ret = NULL;
	filename = create_temp_file();
	if (!filename)
		clear_exit(sh, 1);
	while (1)
	{
		ret = readline("> ");
		if (!ret)
		{
			printf("warning: here-document delimited by end-of-file (wanted `%s')\n", get(tmp)->value);
			break ;
		}
		else if (!ft_strcmp(ret, get(tmp)->value))
		{
			free(ret);
			break ;
		}
		else if (!get(tmp)->not_expand)
			ret = expand_heredoc(sh, ret);
		append_doc_to_file(filename, ret);
		free(ret);
	}
	// update_token_to_file(tmp, filename);
	return (filename);
}

void	handle_heredoc(t_shell *sh, t_list **tkns)
{
	t_list	*tmp;
	char *filename;

	// set_heredoc_signal();
	tmp = *tkns;
	filename = NULL;
	while (tmp)
	{
		if (get(tmp)->type == HEREDOC)
		{
			filename = get_doc(sh, tmp);
			update_token_to_file(tmp, filename);
			free(filename);
		}
		tmp = tmp->next;
	}
}
