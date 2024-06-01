/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:58 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/01 19:23:58 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <time.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libraries/libft/libft.h"

//COLORS
# define ROSE "\x1b[38;207;1m"
# define ROSE_2 "\x1b[38;5;177;1m"
# define LIGHTGREEN "\x1b[38;5;155;1m"
# define LIGHTBLUE "\x1b[38;5;39;1m"
# define LIGHTPURPLE "\x1b[38;5;63;1m"
# define PURPLE "\x1b[38;5;135;1m"
# define PINK "\x1b[38;5;199;1m"
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
	LESSER,
	D_GREATER,
	D_LESSER,
	E_SPACE,
	APPEND,
	OUTFILE,
	INFILE,
	HEREDOC
}	t_token_type;

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
	bool			not_expand;
}	t_token;

//TREE STRUCTURE
typedef enum e_node_type
{
	N_EXEC,
	N_REDIR,
	N_PIPE
}	t_node_type;

typedef struct s_cmd
{
	t_node_type	n_type;
	t_list		*curr_tkn_pos;
}	t_cmd;

typedef struct s_redircmd
{
	t_node_type	n_type;
	t_list		*curr_tkn_pos;
	t_cmd		*cmd;
	char		*file;
	int			mode;
	int			fd;
	int			perm;
}	t_redircmd;

typedef struct s_pipecmd
{
	t_node_type	n_type;
	t_list		*curr_tkn_pos;
	t_cmd		*left;
	t_cmd		*right;
}	t_pipecmd;
typedef struct s_execcmd
{
	t_node_type	n_type;
	t_list		*curr_tkn_pos;
	char		*command;
	char		*command;
	char		**argv;
}	t_execcmd;

//MAIN STRUCTURE
typedef struct s_shell
{
	t_list		*env_lst;
	t_list		*token_lst;
	t_index		*index;
	t_cmd		*cmd;
	char		**paths;
	char		**paths;
}	t_shell;

// MACROS
# define PROMPT "MINISHELL ➜ "
# define OPERATOR "|<>"
# define OUTOFSCOPE "()*;&"
# define OPERATORS_EX "@$?*#-!"

// EXITING THE GLOBAL VARIABLE
extern int	g_signo;

// FUNCTION PROTOTYPES

//main.c
void	sh_loop(t_shell *sh);

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

//cleaning_tree.c
void	free_tree(t_cmd *cmd);

// INPUT FOLDER
// input_checker.c
void	input_check(int argc, char **argv, char **envp);
bool	sintax_validation(char *input);

// input_checker_utils.c
bool	only_white(char *input, int curr_pos);
bool	is_a_pipe(char c);
bool	is_a_bigger(char c);
bool	is_a_smaller(char c);

// sintax_valid.c
bool	check_bigger(char *input, int i);
bool	check_smaller(char *input, int i);
bool	spc_char_check(char *input, int i);
bool	prt_stx_error(char *error, bool exit);

// HANDLING SIGNAL
// signals.c
void	reset_signal(void);

//TOKENIZATION
//tokens.c
void	fill_token_lst(t_shell *sh, char *input);

//tokens_aux.c
void	search_word(char *input, int *end);
void	search_quote(char *input, int *j, char c);
int		search_char(char *str, char c);

//rename_tkn_typ.c
bool	chk_typ(int type, int inf, int sup);
void	repl_tkn_typ(t_token *tkn_src, t_token *tkn_des);
void	review_tkn_typ(t_list *tkn_lst);

//path_aux.c
char	**initialize_array(t_shell *sh, int size);
char	*convert_content_to_string(t_shell *sh, void *content, int type);
void	free_array_on_error(char **array, int i);
char	**list_to_array(t_shell *sh, t_list *list, int type);

//PARSING
//building_tree.c
void	parsing_tree(t_shell *sh);

//construct_tree.c
t_cmd	*execcmd(t_shell *sh, t_list *tkn_pos);
t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd	*pipecmd(t_shell *sh, t_cmd *left, t_cmd *right);
void	fill_execcmd(t_shell *sh, t_execcmd *cmd, char *arg);

//expander.c
void	expand_quotes(t_shell *sh, t_list *token);
void	expand_general(t_shell *sh, t_list *tkn);
char	*expansion(t_list *env_list, char *str, int *i);
char	*get_env(t_list *env_list, char *token);

//expander_aux.c
t_token	*get(t_list *token);
void	remove_node(t_list **list, t_list *node);
char	*simple_expand(char token);
int		check_exp(char key);
char	*get_word(char *str, int *i);

//lexer.c
void	lexer(t_shell *sh, char *input);

//lexer_aux.c
int		is_removable(int type);
void	handle_heredoc(t_list *start);
void	transform_nodes(t_list *start, int type);

//EXEC
//exec_tree.c
void	exec_tree(t_shell *sh, t_cmd *cmd);

//EXTRA AUXILIARS
//print.c
void	print_env(t_shell *sh);
void	print_tokens(t_shell *sh);
void	print_arrays(char **paths);

/*TO BE DEFINED*/
void	get_paths(t_shell *sh);
char	*get_line(t_shell *sh);
int		fork1(t_shell *sh);
void	reinit_shell(t_shell *sh);
#endif
