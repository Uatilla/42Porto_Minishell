/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:08:50 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 13:09:56 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_parent(t_shell *sh, t_cmd *cmd)
{
	t_execcmd *exec;
	int		ret;

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

// int	export(t_shell *sh, t_execcmd *execcmd, bool tree)
// {
// 	char	*key;
// 	char	*value;
// 	int i;

// 	i = 0;
// 	key = NULL;
// 	value = NULL;
// 	if (execcmd->argv[1])
// 	{
// 		value = ft_strchr(execcmd->argv[1], '=');
// 		if (value)
// 		{
			
// 		}
// 		if (!tree)
// 			att_env(sh, key, value);
// 	}
// 	else if (tree)
// 		print_export(sh);
// 	return (0);
// }

void extract_key_value(const char *input, char **key, char **value) {
    char *equal_sign;
    size_t key_length;

    equal_sign = strchr(input, '=');

    if (equal_sign) {
        // '=' found, split the input into key and value
        key_length = equal_sign - input;
        *key = strndup(input, key_length);
        *value = strdup(equal_sign + 1);
    } else {
        // '=' not found, set key and value appropriately
        *key = strdup(input);
        *value = NULL;
    }
}

int export(t_shell *sh, t_execcmd *execcmd, int procs) 
{
    char *key;
    char *value;
    // int i;

    // i = 0;
    key = NULL;
    value = NULL;
    if (execcmd->argv[1]) 
	{
        extract_key_value(execcmd->argv[1], &key, &value);
        if (procs == TREE)
            att_env(sh, key, value);
    }
	else if (procs == TREE)
	{
        print_export(sh);
    }
    // Free the allocated memory for key and value if they were allocated
    if (key) 
		free(key);
    if (value) 
		free(value);
    return (0);
}