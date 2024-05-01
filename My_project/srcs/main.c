/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/01 18:45:33 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	print_tokens(t_shell *sh)
{
	t_token	*token_content;
	t_list	*tmp;

	tmp = sh->token_lst;
	while (tmp)
	{
		token_content = tmp->content;
		printf("Token %02d: ", token_content->pos);
		printf(BLUE_BG"%s"COLOR_RESET, token_content->value);
		printf("\nType: %d\nState: %d\n\n", token_content->type,
			token_content->state);
		tmp = tmp->next;
	}
}

void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	ft_bzero(sh->index, sizeof(t_index));
}

void	sh_loop(t_shell *sh)
{
	char	*prompt_input;
	char	*trimmed_input;
	/*This should be an item inside the structure because this
	variable must be used (probabily) in other functions.*/
	(void) sh;
	while (1)
	{
		prompt_input = readline(PROMPT);
		add_history(prompt_input);
		if (!ft_strncmp(prompt_input, "exit", 5)) // just to exit with clear 
			clear_exit(sh, 1);
		if (!sintax_validation(prompt_input))
			sh_loop(sh);
		trimmed_input = ft_strtrim(prompt_input, "\t ");
		free(prompt_input);
		fill_token_lst(sh, trimmed_input); //tokenization without state;
		print_tokens(sh); // just print
		reinit_shell(sh); // free tokenlist and set t_index to zero
		free(trimmed_input);
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
