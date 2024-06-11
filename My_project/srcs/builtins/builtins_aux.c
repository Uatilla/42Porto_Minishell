/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:09:29 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/11 19:43:32 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_args(char **input)
{
	int	argc;

	argc = 1;
	while (input[argc])
	{
		if (argc >= 2 && !ft_strcmp(input[0], "cd"))
		{
			custom_error("bash: cd", "too many arguments", g_signo);
			return (false);
		}
		else if (argc >= 1 && !ft_strcmp(input[0], "pwd"))
		{
			return (false);
		}
		argc++;
	}
	return (true);
}

int	export_parent(t_shell *sh, t_cmd *cmd)
{
	t_execcmd	*exec;
	int         ret;

	exec = get_exec_node(sh, cmd);
	ret = 0;
	if (cmd->n_type == N_REDIR)
	{
		if (exec->argv[1])
			ret = export(sh, exec, PARENT);
		else
			return (40);
	}
	else
		ret = export(sh, exec, PARENT);
	return (ret);
}

void	extract_key_value(const char *input, char **key, char **value)
{
	char	*equal_sign;
	size_t	key_length;

	equal_sign = ft_strchr(input, '=');
	if (equal_sign)
	{
		key_length = equal_sign - input;
		*key = ft_substr(input, 0, key_length);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(input);
		*value = NULL;
	}
}
