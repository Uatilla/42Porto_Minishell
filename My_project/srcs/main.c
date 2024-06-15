/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 13:32:15 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	run_loop(t_shell *sh, char *prompt_input, int status)
{
	while (1)
	{
		set_signals();
		prompt_input = get_line(sh);
		if (!prompt_input)
			sh_loop(sh);
		if (!sintax_validation(prompt_input))
			sh_loop(sh);
		set_main_signal();
		lexer(sh, prompt_input);
		if (fork1(sh) == 0)
		{
			set_child_signals();
			parsing_tree(sh);
			exec_tree(sh, sh->cmd);
		}
		set_main_signal();
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			g_signo = WEXITSTATUS(status);
		if (sh->nbr_pipes == 0)
			builtins_parent(sh);
		printf("%s\n", prompt_input);
		free(prompt_input);
		reinit_shell(sh);
	}
}

/*This should be an item inside the structure because this
variable must be used (probabily) in other functions.*/
void	sh_loop(t_shell *sh)
{
	char	*prompt_input;
	int		status;

	prompt_input = NULL;
	status = 0;
	run_loop(sh, prompt_input, status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	input_check(argc, argv);
	init_shell(&sh, envp);
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}

// ctrl-D on empty prompt

//     quit minishell
//     echo $? must display 0

// ctrl-C in cat without arguments

//     ^C
//     echo $? must display 130

// ctrl-\ in cat without arguments

//     \Quit (core dumped)
//     echo $? must display 131
