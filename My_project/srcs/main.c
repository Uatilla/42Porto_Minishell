/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/29 17:39:13 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signo;

void	print_tokens(t_shell *sh)
{
	t_token *token_content;
	t_list *tmp = sh->token_lst;

	while (tmp)
	{
		token_content = tmp->content;
		printf("Pos: %d\nValue:%s$\nType: %d\nState: %d\n\n", token_content->pos, token_content->value, token_content->type, token_content->state);
		tmp = tmp->next;
	}
}

void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	ft_bzero(sh->index, sizeof(t_index));
}

bool	chk_typ(int type, int inf, int sup)
{
	return(type >= inf && type <= sup);
}

void	review_tkn_typ(t_list *tkn_lst)
{
	t_list	*tmp;
	t_token	*tkn_cont;
	//t_token	*tkn_to_review;

	tmp = tkn_lst;
	while (tmp)
	{
		tkn_cont = tmp->content;
		if (chk_typ(tkn_cont->type, GREATER, D_LESSER))
		{
			if (chk_typ(((t_token *)(tmp->next->content))->type, E_SPACE, E_SPACE) && \
				(chk_typ(((t_token *)(tmp->next->next->content))->type, WORD, WORD)))
				printf(" Space + WORD\n"); // Passar o node com o fato gerador
				//type tkn_content->type de acordo esse fato gerador voce modifica o conteudo.
			else if (((t_token *)(tmp->next->content))->type == WORD)
				printf(" WORD\n");
			
			//printf("Type: %d content %d\n", tkn_to_review->type, tkn_to_review->pos);
		}
		tmp = tmp->next;
	}
}

void	sh_loop(t_shell *sh)
{
	char	*prompt_input; 
	/*This should be an item inside the structure because this
	variable must be used (probabily) in other functions.*/
	(void) sh;
	while (1)
	{
		prompt_input = readline(PROMPT);
		add_history(prompt_input);
		if (!ft_strncmp(prompt_input, "exit", 4)) // just to exit with clear 
			clear_exit(sh, 1);
		if (!sintax_validation(prompt_input))
			sh_loop(sh);
		fill_token_lst(sh, prompt_input); //tokenization without state;
		review_tkn_typ(sh->token_lst);
		//print_tokens(sh); // just print
		reinit_shell(sh); // free tokenlist and set t_index to zero
		free(prompt_input);
	}
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	fill_env(sh, env_var);
	sh->index = malloc(sizeof(t_index));
	ft_bzero(sh->index, sizeof(t_index));
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
