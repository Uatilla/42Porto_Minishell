/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:37:50 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/14 16:54:38 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quoted_value(char *value)
{
	char	*quoted_value;
	char	*temp;

	if (!value)
		return (NULL);
	temp = ft_strjoin("\"", value);
	quoted_value = ft_strjoin(temp, "\"");
	free(temp);
	return (quoted_value);
}

void	process_element(char **array, t_env *content, int index)
{
	char	*temp[2];

	temp[0] = NULL;
	temp[1] = NULL;
	if (content->visible && ft_strcmp(content->key, "_"))
	{
		temp[1] = get_quoted_value(content->value);
		if (!temp[1])
		{
			array[index] = ft_strdup(content->key);
			free(temp[1]);
			return ;
		}
		temp[0] = ft_strjoin(content->key, "=");
		array[index] = ft_strjoin(temp[0], temp[1]);
		free(temp[0]);
		free(temp[1]);
	}
	else
		array[index] = ft_strdup("");
}

void	populate_array(char **array, t_list *env, int size)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = env;
	while (i < size)
	{
		process_element(array, tmp->content, i);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
}

char	**list_to_array_export(t_list *env)
{
	char	**array;
	int		size;

	size = ft_lstsize(env);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	populate_array(array, env, size);
	return (array);
}
