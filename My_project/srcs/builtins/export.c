/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:08:50 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 21:27:47 by lebarbos         ###   ########.fr       */
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
			if (search_char("[]/{}!^$-+# \t", export[i]))
				return (false);
			i++;
		}
	}
	return (true);
}

void	free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

int	handle_invalid_identifier(char *arg, int procs)
{
	if (procs == TREE)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}

int	process_arguments(t_shell *sh, t_execcmd *execcmd, int procs)
{
	int		ret;
	int		i;
	char	*key;
	char	*value;

	ret = 0;
	i = 1;
	while (execcmd->argv[i])
	{
		if (!check_export(execcmd->argv[i]))
			ret = handle_invalid_identifier(execcmd->argv[i], procs);
		else
		{
			extract_key_value(execcmd->argv[i], &key, &value);
			if (procs == PARENT)
				att_env(sh, key, value);
			free_key_value(key, value);
		}
		i++;
	}
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
