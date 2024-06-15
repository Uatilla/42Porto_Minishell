/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:40:49 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 19:59:37 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_token_to_file(t_list *token, char *filename)
{
	if (get(token)->value)
		free(get(token)->value);
	get(token)->value = ft_strdup(filename);
	free(filename);
}

void	handle_readline(t_shell *sh, t_list *tmp, char *filename, char *input)
{
	char	*ret;

	while (1)
	{
		ret = readline("> ");
		if (!ret || !ft_strcmp(ret, get(tmp)->value))
		{
			if (ret)
				free(ret);
			free(input);
			free(filename);
			clear_exit(sh, 0);
		}
		if (!get(tmp)->not_expand)
			ret = expand_heredoc(sh, ret);
		append_doc_to_file(filename, ret);
		free(ret);
	}
}

void	get_doc(t_shell *sh, t_list *tmp, int i, char *input)
{
	char	*filename;
	int		status;

	status = 0;
	filename = create_temp_file(sh, get(tmp)->value, i);
	if (!filename)
		clear_exit(sh, 1);
	if (fork1(sh) == 0)
	{
		set_heredoc_signal();
		handle_readline(sh, tmp, filename, input);
	}
	waitpid(0, &status, 0);
	update_token_to_file(tmp, filename);
	if (WIFEXITED(status))
		g_signo = WEXITSTATUS(status);
	if (g_signo == 130)
	{
		free(input);
		reinit_shell(sh);
		sh_loop(sh);
	}
}

void	handle_heredoc(t_shell *sh, t_list **tkns, char *input)
{
	t_list	*tmp;
	int		i;

	tmp = *tkns;
	i = 13;
	while (tmp)
	{
		if (get(tmp)->type == HEREDOC)
			get_doc(sh, tmp, i++, input);
		tmp = tmp->next;
	}
}
