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
# include "../libraries/libft/libft.h"

	// STRUCTURES
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			visible;
	//struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_list		*env_lst;
}	t_shell;

// FUNCTION PROTOTYPES
// ENVIRONMENT
// env.c
void	fill_env(t_shell *sh, char **env_var);

//exit.c
void	free_env_list(t_list **env_lst);
void	clear_exit(t_shell *sh, int status);
#endif
