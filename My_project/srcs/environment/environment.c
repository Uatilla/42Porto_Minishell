/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:38:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/12 11:53:33 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_content(t_shell *sh, char *key, char *value, bool visible)
{
	t_env *content;

	content = NULL;
	ft_bzero(content, sizeof(t_env));
	if (!content)
		clear_exit(sh, 1);
	content->key = ft_strdup(key);
	if (value)
		content->value = ft_strdup(value);
	content->visible = visible;
	return (content);
}
void	init_empty_env(t_shell *sh)
{
	char	*pwd;
	t_env	*pwd_node;
	t_env	*shell_level;
	t_env	*old_pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	pwd_node = get_content(sh, "PWD", pwd, true);
	shell_level = get_content(sh, "SHLVL", "1", true);
	old_pwd = get_content(sh, "OLDPWD", NULL, true);
	ft_lstadd_back(&sh->env_lst, ft_lstnew(shell_level));
	ft_lstadd_back(&sh->env_lst, ft_lstnew(pwd_node));
	ft_lstadd_back(&sh->env_lst, ft_lstnew(old_pwd));
}

char	*get_value(char *env_var, int pos)
{
	char	*value;
	int		size;

	size = (int)ft_strlen(&env_var[pos + 1]);
	value = ft_calloc(1, sizeof(char) * (size + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, &env_var[pos + 1], size + 1);
	return (value);
}

char	*get_key(char *env_var, int pos)
{
	char	*key;

	key = ft_calloc(1, sizeof(char) * (pos + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, &env_var[0], pos + 1);
	return (key);
}

void	free_path(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	get_paths(t_shell *sh)
{
	char	*path_aux;

	if (sh->paths)
		free_path(sh->paths);
	path_aux = get_path_aux(sh->envp);
	if (path_aux)
		sh->paths = ft_split(path_aux, ':');
	free(path_aux);
}

/*Put the environment variables in a linked list.*/
void	fill_env(t_shell *sh, char **env_var)
{
	char	*sep;
	int		pos;
	t_env	*node_content;
	t_list	*new_node;

	pos = 0;
	while (*env_var)
	{
		sep = ft_strchr(*env_var, '=');
		if (sep)
		{
			node_content = ft_calloc(1, sizeof(t_env));
			if (!node_content)
				clear_exit(sh, 1);
			pos = (int)(sep - *env_var);
			node_content->key = get_key(*env_var, pos);
			node_content->value = get_value(*env_var, pos);
			node_content->visible = true;
			if (!(node_content->key) || !(node_content->value))
				clear_exit(sh, 1);
			new_node = ft_lstnew(node_content);
			ft_lstadd_back(&sh->env_lst, new_node);
		}
		env_var++;
	}
}
