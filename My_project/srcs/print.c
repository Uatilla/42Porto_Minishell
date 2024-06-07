/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:54:33 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/06 19:20:51 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_shell *sh)
{
	t_token	*token_content;
	t_list	*tmp;
	char	*type[] = {YELLOW "WORD" COLOR_RESET, RED "PIPE" COLOR_RESET, RED "GREATER" COLOR_RESET, RED "LESSER" COLOR_RESET, RED "D_GREATER" COLOR_RESET, RED "D_LESSER" COLOR_RESET, LIGHTBLUE "E_SPACE" COLOR_RESET, LIGHTGREEN"APPEND" COLOR_RESET, LIGHTGREEN "OUTFILE" COLOR_RESET, LIGHTGREEN "INFILE"COLOR_RESET, LIGHTGREEN"HEREDOC" COLOR_RESET};
	char	*state[] = {PINK"GENERAL"COLOR_RESET, PURPLE"IN_DQUOTES"COLOR_RESET, LIGHTPURPLE"IN_SQUOTES" COLOR_RESET};
	char	*expand[] = {"EXPANDE", "NAO_EXPANDE"};

	tmp = sh->token_lst;
	while (tmp)
	{
		token_content = tmp->content;
		printf("Token %02d: ", token_content->pos);
		printf(BLUE_BG"%s"COLOR_RESET, token_content->value);
		printf("\nType: %s\nState: %s\n", type[token_content->type],
			state[token_content->state]);
		if (token_content->type == HEREDOC)
			printf("Type of heredoc: %d %s\n",
				token_content->not_expand, expand[token_content->not_expand]);
		tmp = tmp->next;
	}
}

void	print_env(t_shell *sh)
{
	t_env	*env_content;
	t_list	*tmp;

	tmp = sh->env_lst;
	while (tmp)
	{
		env_content = tmp->content;
		printf("%s=%s\n", env_content->key, env_content->value);
		tmp = tmp->next;
	}
}
