/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:16:52 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/06 19:19:06 by lebarbos         ###   ########.fr       */
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
	input = readline(PROMPT);
	//THIS FUNCTION WAS
	if (!input)
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		clear_exit(sh, 1);
	}
	add_history(input);
	if (!ft_strncmp(input, "exit", 5)) // just to exit with clear 
		clear_exit(sh, 1);
	}
	return (pid);
}

char	**list_to_array(t_shell *sh, t_list *list, int type)
{
	t_env *env;
	char *temp;

	env = NULL;
	temp = NULL;
    int size = ft_lstsize(list);
    char **array = malloc((size + 1) * sizeof(char *));
    if (!array) {
        clear_exit(sh, 1);
    }

    int i = 0;
    while (i < size) {
        void *content = list->content;
        char *value = NULL;

        if (type == 1)
            value = ft_strdup(((t_token *)content)->value);
		else if (type == 2)
		{
			env = (t_env *)content;
            temp = ft_strjoin(env->key, "=");
            value = ft_strjoin(temp, env->value);
            free(temp);
		}
        array[i] = ft_strdup(value);
        if (!array[i]) 
		{
            int j = 0;
            while (j < i) 
			{
                free(array[j]);
                j++;
            }
            free(array);
			free(value);
            clear_exit(sh, 1);
        }
		free(value);
        list = list->next;
        i++;
    }
    array[size] = NULL;  // Adiciona um ponteiro NULL no final do array
    return (array);
}

char	*ft_get_path_aux(char **envp)
{
	int		i;
	char	*path_aux;

	i = 0;
	path_aux = NULL;
	if (!envp[0])
		path_aux = ft_strdup("/usr/bin:/bin");
	else
	{
		while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
			i++;
		if (envp[i] && envp[i][5] != '\0')
			path_aux = ft_strdup(envp[i] + 5);
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
	int		status;
	int		pid;

	(void) sh;
	while (1)
	{
		prompt_input = get_line(sh);
		if (!prompt_input)
			sh_loop(sh);
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
	set_signals();
	//print_env(&sh);
	sh_loop(&sh);
	clear_exit(&sh, 0);
	return (0);
}
