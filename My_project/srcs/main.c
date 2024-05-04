/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/04 14:53:19 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	ft_bzero(sh->index, sizeof(t_index));
}

bool	chk_typ(int type, int inf, int sup)
{
	return(type >= inf && type <= sup);
}

void	repl_tkn_typ(t_token *tkn_src, t_token *tkn_des)
{
	int	new_type;

	if (tkn_src->type == GREATER)
		new_type = OUTFILE;
	else if (tkn_src->type == LESSER)
		new_type = INFILE;
	else if (tkn_src->type == D_GREATER)
		new_type = APPEND;
	else if (tkn_src->type == D_LESSER)
		new_type = HEREDOC;
	else
		return ;
	tkn_des->type = new_type;
		
}
/*Changes the type of the next node if the current node is an operator type.*/
void	review_tkn_typ(t_list *tkn_lst)
{
	t_list	*tmp;
	t_token	*tkn_cont;
	t_token *tkn_src;
	t_token *tkn_des;

	tmp = tkn_lst;
	while (tmp)
	{
		tkn_cont = tmp->content;
		if (chk_typ(tkn_cont->type, GREATER, D_LESSER))
		{
			if (chk_typ(((t_token *)(tmp->next->content))->type, WORD, WORD))
			{
				tkn_src = tmp->content;
				tkn_des = tmp->next->content;
			}
			else if (chk_typ(((t_token *)(tmp->next->content))->type, \
					E_SPACE, E_SPACE))
			{
				tkn_src = tmp->content;
				tmp = tmp->next;
				tkn_des = tmp->next->content;
			}
			repl_tkn_typ(tkn_src, tkn_des);
		}
		tmp = tmp->next;
	}
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
		review_tkn_typ(sh->token_lst);
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
	print_env(&sh);
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}
