/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/21 20:27:01 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signo;

void	search_quote(char *input, int *j, char c)
{
	(*j)++;
	while(input[*j] != c)
		(*j)++;
	if(input[*j] == c)
		(*j)++;
}

void	search_word(char *input, int *end)
{
	int	quotes;

	if (input[*end] && ft_strchr("<>|", input[*end]))
	{
		while (input[*end] && ft_strchr("<>|", input[*end]))
			(*end)++;
		return ;
	}
	while (input[*end] && !ft_strchr("\t\n\v\f\r ", input[*end]) && !ft_strchr("<>|", input[*end]))
	{
		if (ft_strchr("\"\'", input[*end]))
		{
			quotes = !quotes;
			search_quote(input, end, input[*end]);
		}
		else
			(*end)++;
	}
}

void	fill_token_lst(t_shell *sh, char *input)
{
	t_token *node_content;
	// t_list	*new_node;
	// char	*value;

	node_content = ft_calloc(1, sizeof(t_token));
	if (!node_content)
		clear_exit(sh, 1);
	while (input[sh->index->start])
	{
		while (ft_isspace(input[sh->index->start]))
			sh->index->start++;
		sh->index->end = sh->index->start;
		if(input[sh->index->end] == '\"' || input[sh->index->end] == '\'')
		{
			search_quote(input, &sh->index->end, input[sh->index->end]);
			while (!ft_isspace(input[sh->index->end] && input[sh->index->end]))
			{
				if (input[sh->index->end] == '\"' || input[sh->index->end] == '\'')
					search_quote(input, &sh->index->end, input[sh->index->end]);
				else
					search_word(input, &sh->index->end);
			}
		}
		else
			search_word(input, &sh->index->end);
		node_content->value = ft_substr(input, sh->index->start, sh->index->end - sh->index->start);
		// node_content->type = get_token_type(node_content->value);
		node_content->pos = sh->index->pos;
		ft_lstadd_back(&sh->token_lst, ft_lstnew(node_content));
	}
}

void	sh_loop(t_shell *sh)
{
	char	*prompt_input; /*This should be an item inside the structure because this
	variable must be used (probabily) in other functions.*/
	(void) sh;
	while (1)
	{
		prompt_input = readline(PROMPT);
		fill_token_lst(sh, prompt_input);
	}
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	fill_env(sh, env_var);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	input_check(argc, argv, envp);
	init_shell(&sh, envp);
	reset_signal();
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}
