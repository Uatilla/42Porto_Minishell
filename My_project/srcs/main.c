/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/06 19:04:52 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	reinit_shell(t_shell *sh)
{
	free_token_list(&sh->token_lst);
	if (sh->cmd)
		free_tree(sh->cmd);
	ft_bzero(sh->index, sizeof(t_index));
}

void	init_shell(t_shell *sh, char **env_var)
{
	ft_bzero(sh, sizeof(t_shell));
	sh->index = malloc(sizeof(t_index));
	if (!sh->index)
	{
		write(1, "Malloc error!", 14);
		clear_exit(sh, 1);
	}
	ft_bzero(sh->index, sizeof(t_index));
	fill_env(sh, env_var);
	get_paths(sh);
}

int	fork1(t_shell *sh)
{
	int	pid;

	pid = fork();
	sh->pid = pid;
	if (pid == -1)
	{
		printf("Fork failed\n");
		clear_exit(sh, 1);
	}
	return (pid);
}

/*This should be an item inside the structure because this
variable must be used (probabily) in other functions.*/
void	sh_loop(t_shell *sh)
{
	char	*prompt_input;
	int		status;
	int		pid;

	(void) sh;
	while (1)
	{
		prompt_input = get_line(sh);
		if (!prompt_input)
			sh_loop(sh);
		if (!sintax_validation(prompt_input))
			sh_loop(sh);
		lexer(sh, prompt_input);
		pid = fork1(sh);
		printf("loop: %d\n", pid);
		if (pid == 0)
		{
			parsing_tree(sh);
			exec_tree(sh, sh->cmd);
		}
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			g_signo = WEXITSTATUS(status);
		reinit_shell(sh);
		free(prompt_input);
	}
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
