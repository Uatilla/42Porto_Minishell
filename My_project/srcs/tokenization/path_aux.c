/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:07:08 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/01 17:07:33 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**initialize_array(t_shell *sh, int size)
{
	char	**array;

	array = malloc((size + 1) * sizeof(char *));
	if (!array)
		clear_exit(sh, 1);
	return (array);
}

char	*convert_content_to_string(t_shell *sh, void *content, int type)
{
	t_env	*env;
	char	*temp;
	char	*value;

	value = NULL;
	if (type == 1)
		value = ft_strdup(((t_token *)content)->value);
	else if (type == 2)
	{
		env = (t_env *)content;
		temp = ft_strjoin(env->key, "=");
		value = ft_strjoin(temp, env->value);
		free(temp);
	}
	if (!value)
		clear_exit(sh, 1);
	return (value);
}

void	free_array_on_error(char **array, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(array[j]);
		j++;
	}
	free (array);
}

char	**list_to_array(t_shell *sh, t_list *list, int type)
{
	int		size;
	char	**array;
	char	*value;
	int		i;

	size = ft_lstsize(list);
	array = initialize_array(sh, size);
	i = 0;
	if (!sh->env_lst)
		return (NULL);
	while (i < size)
	{
		value = convert_content_to_string(sh, list->content, type);
		array[i] = ft_strdup(value);
		free(value);
		if (!array[i])
		{
			free_array_on_error(array, i);
			clear_exit(sh, 1);
		}
		list = list->next;
		i++;
	}
	array[size] = NULL;
	return (array);
}
