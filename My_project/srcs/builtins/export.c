/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:08:50 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/15 16:58:10 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(char *export)
{
	int	i;

	i = 0;
	if (ft_isnumber(export[0]) || export[0] == '=')
		return (false);
	else
	{
		while (export[i] && export[i] != '=')
		{
			if (search_char("[]/{}!^$-+#?., \t", export[i]))
				return (false);
			i++;
		}
	}
	return (true);
}

int	handle_invalid_identifier(char *arg, int procs)
{
	if (procs == TREE)
	{
		if (arg[0] == '-')
		{
			write(2, "minishell: export: ", 20);
			write(2, arg, 2);
			write(2, ": invalid option\nexport: usage: ", 33);
			write(2, "export [name[=value] ...] or export\n", 37);
			return (2);
		}
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}

int	procs_args_aux(t_shell *sh, t_execcmd *execcmd, int procs, int ret)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (execcmd->argv[++i])
	{
		if (!check_export(execcmd->argv[i]))
			return (handle_invalid_identifier(execcmd->argv[i], procs));
		else
		{
			extract_key_value(execcmd->argv[i], &key, &value);
			if (procs == PARENT)
			{
				if (!value && find_env_node(sh->env_lst, key))
				{
					free_key_value(key, value);
					return (0);
				}
				att_env(sh, key, value);
			}
			free_key_value(key, value);
		}
	}
	return (ret);
}

int	process_arguments(t_shell *sh, t_execcmd *execcmd, int procs)
{
	int	ret;

	ret = 0;
	ret = procs_args_aux(sh, execcmd, procs, ret);
	return (ret);
}

int	export(t_shell *sh, t_execcmd *execcmd, int procs)
{
	int	ret;
	int	i;

	i = 1;
	ret = 0;
	if (execcmd->argv[i])
		ret = process_arguments(sh, execcmd, procs);
	else if (procs == TREE)
		print_export(sh);
	return (ret);
}
