/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/23 18:49:13 by lebarbos         ###   ########.fr       */
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

int	search_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	search_word(char *input, int *end)
{
	if (input[*end] && search_char("<>|", input[*end]))
	{
		while (input[*end] && search_char("<>|", input[*end]))
			(*end)++;
		return ;
	}
	while (input[*end] && !search_char("\t\n\v\f\r ", input[*end]) && !search_char("<>|", input[*end]))
	{
		if (search_char("\"\'", input[*end]))
			search_quote(input, end, input[*end]);
		else
			(*end)++;
	}
}

void	print_tokens(t_shell *sh)
{
	t_token *token_content;
	t_list *tmp = sh->token_lst;

	while (tmp)
	{
		token_content = tmp->content;
		printf("Pos: %d\nValue:%s\nType: %d\n\n", token_content->pos, token_content->value, token_content->type);
		tmp = tmp->next;
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

int	get_token_type(char *token)
{
	if (token[0] == '|' && !search_char("<>|", token[1]))
		return (PIPE);
	else if (token[0] == '>' && !search_char("<>|", token[1]))
		return(GREATER);
	else if (token[0] == '<' && !search_char("<>|", token[1]))
		return (LESSER);
	else if (token[0] == '>' && token[1] == '>' && !search_char("<>|", token[2]))
		return (D_GREATER);
	else if (token[0] == '<' && token[1] == '<' && !search_char("<>|", token[2]))
		return (D_LESSER);
	else
		return (WORD);
}

void	fill_token_lst(t_shell *sh, char *input)
{
	t_token *node_content;

	node_content = NULL;
	while (input[sh->index->start])
	{
		if (ft_isspace(input[sh->index->start]))
			sh->index->start++;
		else 
		{
			node_content = ft_calloc(1, sizeof(t_token));
			if (!node_content)
				clear_exit(sh, 1);
			end_word(sh, input);
			node_content->value = ft_substr(input, sh->index->start, sh->index->end - sh->index->start);
			node_content->type = get_token_type(node_content->value); // function to set the type of the node;
			node_content->pos = sh->index->pos;
			ft_lstadd_back(&sh->token_lst, ft_lstnew(node_content));
			sh->index->pos++;
			sh->index->start = sh->index->end;
		}
	}
}

void	clear_shell(t_shell *sh)
{
	ft_bzero(sh->index, sizeof(t_index));
}

int	check_operator_order(t_list *token)
{
	t_list *current;
	t_list *previous; 
	t_token	*token_prev;
	t_token *token_curr;

	current = token;
	while (current)
	{
		previous = current;
		current = current->next;
		token_prev = previous->content;
		if (current)
			token_curr = current->content;
		else
		{
			token_curr = NULL;
		}
		if (current && token_prev->type && token_curr->type)
		{
			if (token_prev->type == PIPE && token_curr->type != PIPE)
				continue ;
			else 
				return (1);
		}
	}
	return (0);
}

int	check_syntax(t_list *token_list)
{
	t_list *tmp;
	t_token *token;

	tmp = token_list;
	while (tmp)
	{
		token = tmp->content;
		if (token->value[0] == '|' && token->pos == 0)
			return (1);
		if (token->value[0] == '|' && search_char("<>|", token->value[1]))
			return (1);
		if (token->value[0] == '<' && search_char(">|", token->value[1]))
			return (1);
		if (token->value[0] == '>' && search_char("<|", token->value[1]))
			return (1);
		if (token->value[0] == '>' && token->value[1] == '>' && search_char("<>|", token->value[2]))
			return (1);
		if (token->value[0] == '<' && token->value[1] == '<' && search_char("<>|", token->value[2]))
			return (1);
		tmp = tmp->next;
	}
	if (check_operator_order(token_list))
		return (1);
	return (0);
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
		print_tokens(sh); // print token value and position;
		if (check_syntax(sh->token_lst))
			printf("syntax error\n");
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
