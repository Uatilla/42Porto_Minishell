/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:58 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/11 19:58:00 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libraries/libft/libft.h"

// STRUCTURES
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			visible;
}	t_env;

typedef struct s_shell
{
	t_list		*env_lst;
}	t_shell;


// MACROS
# define PROMPT "MINISHELL ➜ " 

// EXITING THE GLOBAL VARIABLE
extern int	g_signo;

// FUNCTION PROTOTYPES
// ENVIRONMENT FOLDER
// env.c
void	fill_env(t_shell *sh, char **env_var);

// EXIT FOLDER
//exit.c
void	free_env_list(t_list **env_lst);
void	clear_exit(t_shell *sh, int status);

// INPUT FOLDER
// input_checker.c
void    input_check(int argc, char **argv, char **envp);

// HANDLING SIGNAL
// signals.c
void    reset_signal(void);
#endif
