/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/01 15:13:24 by lebarbos         ###   ########.fr       */
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

//COLORS
# define RED "\x1b[38;5;160;1m"
# define ORANGE "\x1b[38;5;172;1m"
# define YELLOW "\x1b[38;5;184;1m"
# define BLUE_BG "\033[38;5;159;48;5;16;1m"
# define COLOR_RESET "\033[0m"

// STRUCTURES
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			visible;
}	t_env;

typedef enum s_token_type
{
	WORD,
	PIPE,
	GREATER,
	OUTFILE,
	LESSER,
	INFILE,
	D_GREATER,
	HERE_DOC,
	D_LESSER,
	APP_END,
	E_SPACE
} t_token_type;

typedef enum s_token_state
{
	GENERAL,
	IN_DQUOTES,
	IN_SQUOTES
}	t_token_state;

typedef struct s_index
{
	int	start;
	int	end;
	int	pos;
}	t_index;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_state	state;
	int				pos;
}	t_token;

typedef struct s_shell
{
	t_list		*env_lst;
	t_list		*token_lst;
	t_index		*index;
}	t_shell;

// MACROS
# define PROMPT "MINISHELL ➜ "
# define OPERATOR "|<>"

// EXITING THE GLOBAL VARIABLE
extern int	g_signo;

// FUNCTION PROTOTYPES
// ENVIRONMENT FOLDER
// env.c
void	fill_env(t_shell *sh, char **env_var);

// EXIT FOLDER
//exit.c
void	free_env_list(t_list **env_lst);
void	free_token_list(t_list **token_list);
void	clear_exit(t_shell *sh, int status);
void	free_token_list(t_list **token_list);
void	free_token_content(void *content);

// INPUT FOLDER
// input_checker.c
void    input_check(int argc, char **argv, char **envp);
bool    sintax_validation(char *input);

// input_checker_utils.c
bool    only_white(char *input, int curr_pos);
bool    is_a_pipe(char c);
bool    is_a_bigger(char c);
bool    is_a_smaller(char c);


// HANDLING SIGNAL
// signals.c
void    reset_signal(void);

//TOKENIZATION
//tokens.c
void	fill_token_lst(t_shell *sh, char *input);

#endif
