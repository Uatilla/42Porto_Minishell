/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:40:49 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 21:42:58 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	update_token_to_file(t_list *token, char *filename)
{
	if (get(token)->value)
		free(get(token)->value);
	get(token)->value = ft_strdup(filename);
}

void	get_doc(t_shell *sh, t_list *tmp, int i)
{
	char	*ret;
	char	*filename;
	int		status;

	ret = NULL;
	status = 0;
	filename = create_temp_file(sh, get(tmp)->value, i);
	if (!filename)
		clear_exit(sh, 1);
	ft_lstadd_back(&sh->heredocs, ft_lstnew(filename));
	if (fork1(sh) == 0)
	{
		set_heredoc_signal();
		while (1)
		{
			ret = readline("> ");
			if (!ret)
			{
				printf("warning: here-document delimited by end-of-file (wanted `%s')\n", get(tmp)->value);
				exit (g_signo);
			}
			else if (!ft_strcmp(ret, get(tmp)->value))
			{
				free(ret);
				exit (g_signo);
			}
			else if (!get(tmp)->not_expand)
				ret = expand_heredoc(sh, ret);
			append_doc_to_file(filename, ret);
			free(ret);
		}
	}
	waitpid(0, &status, 0);
	update_token_to_file(tmp, filename);
	if (WIFEXITED(status))
		g_signo = WEXITSTATUS(status);
	if (g_signo == 130)
	{
		reinit_shell(sh);
		sh_loop(sh);
	}
}

void	handle_heredoc(t_shell *sh, t_list **tkns)
{
	t_list	*tmp;
	int		i;
	// char *filename;

	// filename = NULL;
	tmp = *tkns;
	i = 13;
	while (tmp)
	{
		if (get(tmp)->type == HEREDOC)
		{
			get_doc(sh, tmp, i++);
		}
		tmp = tmp->next;
	}

}
