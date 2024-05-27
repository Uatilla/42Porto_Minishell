/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/27 17:31:59 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	ft_bzero(sh->index, sizeof(t_index));
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	sh->index = malloc(sizeof(t_index));
	//PROTECAO DO MALLOC
	ft_bzero(sh->index, sizeof(t_index));
	fill_env(sh, env_var);
}

char	*get_line(t_shell *sh)
{
	char *input;
	char *trimmed_input;

	input = readline(PROMPT);
	if (!input || !*input)
		sh_loop(sh);
	add_history(input);
	if (!ft_strncmp(input, "exit", 5)) // just to exit with clear 
		clear_exit(sh, 1);
	if (!ft_strcmp(input, "clear"))
	{
		system("clear");
		sh_loop(sh);
	}
	trimmed_input = ft_strtrim(input, "\t ");
	free(input);
	return (trimmed_input);
}

/*This should be an item inside the structure because this
variable must be used (probabily) in other functions.*/
void	sh_loop(t_shell *sh)
{
	char	*prompt_input;

	(void) sh;
	while (1)
	{
		prompt_input = get_line(sh);
		if (!sintax_validation(prompt_input))
			sh_loop(sh);
		lexer(sh, prompt_input);
		fill_token_lst(sh, prompt_input); //tokenization without state;
		review_tkn_typ(sh->token_lst);
		parsing_tree(sh);
		reinit_shell(sh); // free tokenlist and set t_index to zero
		free(prompt_input);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	input_check(argc, argv, envp);
	init_shell(&sh, envp);
	reset_signal();
	//print_env(&sh);
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}
