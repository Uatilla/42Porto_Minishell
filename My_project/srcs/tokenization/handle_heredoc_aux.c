/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:42:00 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/09 11:35:37 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredoc(t_list *token)
{
	t_list	*tkn;

	tkn = token;
	printf("HEEEERE\n");
	while (tkn)
	{
		printf("%s\n", (char *)tkn->content);
		unlink((char *)tkn->content);
		free((char *)tkn->content);
		tkn = tkn->next;
	}
}

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

char	*generate_temp_filename(void)
{
	char	*filename;
	char	*file_aux;
	char	*num;
	int		random_number;
	time_t	t;

	filename = NULL;
	srand((unsigned) time(&t));
	random_number = rand();
	file_aux = ft_strdup(".tmp_heredoc_");
	num = ft_itoa(random_number);
	filename = ft_strjoin(file_aux, num);
	free(file_aux);
	free(num);
	return (filename);
}