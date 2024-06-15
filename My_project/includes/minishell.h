/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:58 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/15 13:31:39 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <time.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
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

//ERROR MESSAGES
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|'"

// STRUCTURES
typedef enum s_proc
{
	PARENT,
	TREE
}	t_proc;

typedef enum s_folder
{
	FOLDER_NAME,
	PARENT_FOLDER,
	NOTHING
}	t_folder;

typedef struct s_cd
{
	t_folder	*type;
}	t_cd;

typedef enum s_signal
{
	PARENT_SIG,
	CAT_SIG,
	HEREDOC_SIG
}	t_signal;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	visible;
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
	char		**argv;
}	t_execcmd;

//MAIN STRUCTURE
typedef struct s_shell
{
	t_list		*env_lst;
	t_list		*token_lst;
	t_index		*index;
	int			pid;
	int			nbr_pipes;
	t_cmd		*cmd;
	char		**paths;
	char		**envp;
}	t_shell;

// MACROS
# define PROMPT "MINISHELL ➜ "
# define OPERATOR "|<>"
# define OUTOFSCOPE "!()*;&"
# define OUTOFSCOPE "!()*;&"
# define OPERATORS_EX "@$?*#-!"

// EXITING THE GLOBAL VARIABLE
extern int		g_signo;

// FUNCTION PROTOTYPES
//main.c
void			sh_loop(t_shell *sh);

//main_aux.c
void			reinit_shell(t_shell *sh);
void			init_shell(t_shell *sh, char **env_var);
int				fork1(t_shell *sh);

//BUILTINS FOLDER
//builtins_aux.c
bool			check_args(char **input);
int				export_parent(t_shell *sh, t_cmd *cmd);
void			extract_key_value(const char *input, char **key, char **value);
//chdir.c
void			cd_others(t_shell *sh, char *dest_folder);
// void			cd_home(t_shell *sh);
void	cd_home(t_shell *sh, char *home_path);
void			exec_cd(t_shell *sh, char **argv);
int				change_dir(t_shell *sh, t_execcmd *cmd);
//chdir_aux.c
bool			check_dots(char *input);
bool			check_option(char *input);
bool			sintax_valid_cd(char *cmd, char **argv, t_shell *sh);
//check_builtins.c
int				execute_builtin(t_shell *sh, t_execcmd *cmd, int procs);
bool			isbuiltin(char *cmd);
bool			isbuiltin_parent(char *cmd);
void			builtins_parent(t_shell *sh);
//echo.c
bool			check_word(char *word);
void			exec_echo(char **argv, int argc);
int				check_flag(char **argv);
int				echo(t_shell *sh, t_execcmd *cmd);
//env_aux.c
void			remove_env_node(t_list **list, t_list *node);
t_list			*find_env_node(t_list *list, char *key);
void			att_env(t_shell *sh, char *key, char *new_value);
//env.c
t_list			*find_last_word(t_list *token_lst);
t_env			*create_env_node(char *key, char *value);
void			update_env_list(t_shell *sh, t_env *node_content);
int				env(t_shell *sh, t_execcmd *cmd);
t_execcmd		*get_exec_node(t_shell *sh, t_cmd *node);
//exit.c
int				exit_bin(t_shell *sh, t_execcmd *exit_cmd, int procs);
int				is_exit_code(char *nbr);
bool			is_valid_number(char *nbr, long long *exit_code);
//exit_utils.c
long long		ft_atol(const char *nptr);
char			*ft_lltoa(long long n);

//export_aux.c
void			print_export(t_shell *sh);
char			**ordenate_envp(t_list *env_lst);
void			bubble_sort(char **array, int size);
void			bubble_sort_recursive(char **array, int size);
void			swap(char **x, char **y);
//export_aux2.c
char			**list_to_array_export(t_list *env);
void			populate_array(char **array, t_list *env, int size);
void			process_element(char **array, t_env *content, int index);
char			*get_quoted_value(char *value);
//export.c
int				export(t_shell *sh, t_execcmd *execcmd, int procs);
int				process_arguments(t_shell *sh, t_execcmd *execcmd, int procs);
int				handle_invalid_identifier(char *arg, int procs);
void			free_key_value(char *key, char *value);
int				check_export(char *export);
//pwd.c
int				pwd(t_shell *sh, t_execcmd *cmd);
void			exec_pwd(t_shell *sh);
bool			sintax_valid_pwd(char *cmd, char **argv, t_shell *sh);
//unset.c
int				unset(t_shell *sh, t_execcmd *cmd, int procs);

//ENVIRONMENT
//environment.c
void			init_empty_env(t_shell *sh);
char			*get_value(char *env_var, int pos);
char			*get_key(char *env_var, int pos);
void			fill_env(t_shell *sh, char **env_var);
//environment_path.c
void			free_path(char **array);
void			get_paths(t_shell *sh);

//EXEC
//exec_tree_aux.c
bool			is_file(char *file);
bool			is_directory(char	*cmd);
void			create_pipe(int p[2], t_shell *sh);
void			run_pipe_child(t_shell *sh, t_cmd *cmd, int p[2], int child);
bool			handle_command_errors(t_execcmd *excmd);
//exec_tree.c
void			exec_tree(t_shell *sh, t_cmd *cmd);
void			run_pipe(t_shell *sh, t_cmd *cmd);
void			run_redir(t_shell *sh, t_cmd *cmd);
void			run_exec(t_shell *sh, t_cmd *cmd);
void			execute_command(t_shell *sh, t_execcmd *excmd);

//EXIT_FILES
//cleaning_tree.c
void			free_tree(t_cmd *cmd);
//exit_aux.c
void			clear_exit(t_shell *sh, int status);
//exit.c
void			free_token_list(t_list **token_list);
void			free_env_list(t_list **env_lst);
void			free_token_content(void *content);
void			free_env_content(void *content);
void			custom_error(char *bash, char *file, char *message, int error);

//EXPANSION FOLDER
//expander.c
char			*handle_word_type(t_shell *sh, t_list *tkn, int *i);
void			update_token_value(t_list *tkn, char *new_token);
void			expand_general(t_shell *sh, t_list *tkn);
void			expand_quotes(t_shell *sh, t_list *token);
//expander_aux2.c
char			*get_env(t_list *env_list, char *token);
char			*expansion(t_shell *sh, char *str, int *i);
void			handle_non_general_state(t_list *tkn);
void			handle_heredoc_type(t_list *tkn);
//expander_aux.c
char			*get_word(char *str, int *i);
int				check_exp(char key);
t_token			*get(t_list *token);
char			*simple_expand(t_shell *sh, char token);
void			remove_node(t_list **list, t_list *node);

// INPUT FOLDER
// input_checker_utils.c
bool			only_white(char *input, int curr_pos);
bool			is_a_pipe(char c);
bool			is_a_bigger(char c);
bool			is_a_smaller(char c);
void			input_check(int argc, char **argv);
// input_checker.c
bool			sintax_validation(char *input);
bool			ch_fst(char *input, char search);
int				search_c_quote(char *input, int i, char search);
bool			prt_stx_error(char *error, bool exit);
// sintax_valid.c
bool			check_bigger(char *input, int i);
bool			check_smaller(char *input, int i);
bool			spc_char_check(char *input, int i);

//PARSING
//building_tree.c
t_cmd			*parse_redir(t_shell *sh, t_cmd *cmd);
t_cmd			*parse_exec(t_shell *sh, t_list *tkn_pos);
t_cmd			*parse_pipe(t_shell *sh, t_list *tkn_pos);
void			parsing_tree(t_shell *sh);
int				count_args(t_shell *sh, t_list *tkn_pos);
//construct_tree.c
void			fill_execcmd(t_shell *sh, t_execcmd *cmd, char *arg);
t_cmd			*execcmd(t_shell *sh, t_list *tkn_pos);
t_cmd			*get_redir(t_cmd *cmd);
t_cmd			*redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd			*pipecmd(t_shell *sh, t_cmd *left, t_cmd *right);
//path_functions.c
char			*find_path(t_shell *sh, char *command);
char			*ft_check_command_location(t_shell *sh, \
					char *command, char *path_i);

// HANDLING SIGNAL
// signals.c
void			sigint_child_handler(int signo);
void			set_child_signals(void);
void			set_main_signal(void);
void			sigint_handler(int signo);
void			set_signals(void);
//signals_heredoc.c
void			sigint_child_handler(int signo);
void			set_heredoc_signal(void);

//TOKENIZATION
//handle_heredoc_aux.c
char			*expand_heredoc(t_shell *sh, char *str);
char			*generate_temp_filename(t_shell *sh, char *file, int i);
void			append_doc_to_file(char *filename, char *content);
char			*create_temp_file(t_shell *sh, char *file, int i);
//handle_heredoc.c
void			handle_readline(t_shell *sh, t_list *tmp, char *filename);
void			update_token_to_file(t_list *token, char *filename);
void			get_doc(t_shell *sh, t_list *tmp, int i);
void			handle_heredoc(t_shell *sh, t_list **tkns);
//lexer_aux.c
int				is_removable(int type);
void			transform_nodes(t_list *start, int type);
void			set_heredoc_type(t_list *start);
void			join_non_removable_nodes(t_shell *sh, t_list **tkns);
void			remove_removable_nodes(t_shell *sh, t_list **tkns);
//lexer_home.c
char			*expand_home(t_shell *sh, t_list *tmp);
bool			is_home(t_list *tmp);
//lexer_expander.c
void			expand_general_tokens(t_shell *sh, t_list **tokens);
void			expand_quote_tokens(t_shell *sh, t_list **tokens);
//lexer.c
void			clean_tokenlist(t_shell *sh, t_list **tkns);
void			review_tkn_list(t_shell *sh, t_list **tkn);
void			lexer(t_shell *sh, char *input);
//path_aux.c
char			**initialize_array(t_shell *sh, int size);
char			*convert_content_to_string(t_shell *sh, \
					void *content, int type);
void			free_array(char **array, int size);
char			**list_to_array(t_shell *sh, t_list *list, int type);
//path.c
char			*read_and_join_input(char *join);
char			*open_pipe(__attribute__((unused)) t_shell *sh, char *input);
char			*handle_input(t_shell *sh, char *input);
char			*get_line(t_shell *sh);
char			*get_path_aux(char **envp);
//rename_tkn_typ.c
bool			chk_typ(int type, int inf, int sup);
void			repl_tkn_typ(t_token *tkn_src, t_token *tkn_des);
void			def_new_tkn_typ(t_list *tmp);
void			review_tkn_typ(t_list *tkn_lst);
//tokens.c
int				get_token_type(char *token);
void			get_token_state(t_token *token);
void			end_word(t_shell *sh, char *input);
void			fill_token_lst(t_shell *sh, char *input);
//tokens_aux.c
void			search_word(char *input, int *end);
void			search_quote(char *input, int *j, char c);
int				search_char(char *str, char c);

//print.c
void			print_env(t_shell *sh);
void			print_arrays(char **paths);
bool			is_home(t_list *tmp);
char			*expand_home(t_shell *sh, t_list *tmp);
void			print_tokens(t_shell *sh);

#endif
