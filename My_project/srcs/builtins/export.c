/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:08:50 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/11 15:18:12 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_parent(t_shell *sh, t_cmd *cmd)
{
	t_execcmd *exec;
	int		ret;

	exec = get_exec_node(sh, cmd);
	ret = 0;
	printf("Export PID: %d\n", getpid());
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

void extract_key_value(const char *input, char **key, char **value) 
{
    char *equal_sign;
    size_t key_length;

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

int check_export(char *export)
{
    int i;

    i = 0;
    if (ft_isnumber(export[0]) || export[0] == '=')
        return (false);
    else
    {
        while (export[i] && export[i] != '=')
        {
            if(search_char("[]/{}!^$-+# \t", export[i]))
                return (false);
            i++;
        }
    }
    return (true);
}


int export(t_shell *sh, t_execcmd *execcmd, int procs) 
{
    char *key;
    char *value;
    int ret;
    int i;

    key = NULL;
    value = NULL;
    i = 1;
    ret = 0;
    if (execcmd->argv[i]) 
	{
        while(execcmd->argv[i])
        {
            if (!check_export(execcmd->argv[i]))
            {
                if (procs == TREE)
                {
                    ft_putstr_fd("export: `", 2);
                    ft_putstr_fd(execcmd->argv[i], 2);
                    ft_putstr_fd("': not a valid identifier\n", 2);
                }
                ret = 1;
            }
            else
            {
                extract_key_value(execcmd->argv[i], &key, &value);
                if (procs == PARENT)
                    att_env(sh, key, value);
                ret = 0;
                if (key)
                    free(key);
                if (value) 
                    free(value);
            }
            i++;
        }
    }
	else if (procs == TREE)
        print_export(sh);
    return (ret);
}
