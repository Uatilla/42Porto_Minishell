/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/08 22:24:35 by lebarbos         ###   ########.fr       */
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

void	init_empty_env(sh)
{
	char	*sep;
	int		pos;
	t_env	*node_content;
	t_list	*new_node;

	pos = 0;
			node_content = ft_calloc(1, sizeof(t_env));
	
	while (*env_var)
	{
		sep = ft_strchr(*env_var, '=');
		if (sep)
		{
			if (!node_content)
				clear_exit(sh, 1);
			pos = (int)(sep - *env_var);
			node_content->key = get_key(*env_var, pos);
			node_content->value = get_value(*env_var, pos);
			node_content->visible = true;
			if (!(node_content->key) || !(node_content->value))
				clear_exit(sh, 1);
			new_node = ft_lstnew(node_content);
			ft_lstadd_back(&sh->env_lst, new_node);
		}
		env_var++;
	}
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
	if (env_var)
	{
		fill_env(sh, env_var);
		get_paths(sh);
	}
	else
		init_empty_env(sh);
}

int	fork1(t_shell *sh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed\n");
		clear_exit(sh, 1);
	}
	sh->pid = pid;
	return (pid);
}

/*This should be an item inside the structure because this
variable must be used (probabily) in other functions.*/
void	sh_loop(t_shell *sh)
{
	char	*prompt_input;
	int		status;

	(void) sh;
	while (1)
	{
		prompt_input = get_line(sh);
		if (!prompt_input)
			sh_loop(sh);
		if (!sintax_validation(prompt_input))
			sh_loop(sh);
		lexer(sh, prompt_input);
		if (fork1(sh) == 0)
		{
			handle_heredoc(sh, sh->token_lst);
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
	set_signals();
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}
