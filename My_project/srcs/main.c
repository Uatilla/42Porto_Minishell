/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/22 16:42:17 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;
void	sh_loop(t_shell *sh);

void	search_quote(char *input, int *j, char c)
{
	(*j)++;
	while(input[*j] != c && input[*j])
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

void	print_tokens(t_shell *sh)
{
	int	i;
	t_token *token_content;

	i = 0;
	while (i <= sh->index->pos)
	{
		token_content = sh->token_lst->content;
		printf("Pos: %d\nValue:%s\n", token_content->pos, token_content->value);
		sh->token_lst = sh->token_lst->next;
	}
}

void	end_word(t_shell *sh, char *input)
{
	sh->index->end = sh->index->start;
	if (input[sh->index->end] == '\"' || input[sh->index->end] == '\'')
	{
		search_quote(input, &sh->index->end, input[sh->index->end]);
		while (!ft_isspace(input[sh->index->end]) && input[sh->index->end])
		{
			if (input[sh->index->end] == '\"' && input[sh->index->end == '\''])
				search_quote(input, &sh->index->end, input[sh->index->end]);
			else
				search_word(input, &sh->index->end);
		}
	}
	else
		search_word(input, &sh->index->end);
}

void	fill_token_lst(t_shell *sh, char *input)
{
	t_token *node_content;

	while (input[sh->index->start])
	{
		node_content = ft_calloc(1, sizeof(t_token));
		if (!node_content)
			clear_exit(sh, 1);
		if (ft_isspace(input[sh->index->start]))
			sh->index->start++;
		else 
		{
			end_word(sh, input);
			node_content->value = ft_substr(input, sh->index->start, sh->index->end - sh->index->start);
			// node_content->type = get_token_type(node_content->value); // function to set the type of the node;
			node_content->pos = sh->index->pos;
			ft_lstadd_back(&sh->token_lst, ft_lstnew(node_content));
			printf("Pos: %d\nValue:%s$\n\n", node_content->pos, node_content->value);
			free(node_content->value);
			free(node_content);
			sh->index->pos++;
			sh->index->start = sh->index->end;
			sh->token_lst = sh->token_lst->next;
		}
	}
}

void	clear_shell(t_shell *sh)
{
	ft_bzero(sh->index, sizeof(t_index));
}

void	sh_loop(t_shell *sh)
{
	char	*prompt_input; /*This should be an item inside the structure because this
	variable must be used (probabily) in other functions.*/
	(void) sh;
	while (1)
	{
		prompt_input = readline(PROMPT);
		if (!ft_strncmp(prompt_input, "exit", 4)) // just to exit with clear 
			clear_exit(sh, 0);
		fill_token_lst(sh, prompt_input);
		free_token_list(&sh->token_lst);
		clear_shell(sh); //set everything to zero to restart the tokenization
	}
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	sh->index = malloc(sizeof(t_index));
	ft_bzero(sh->index, sizeof(t_index));
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
