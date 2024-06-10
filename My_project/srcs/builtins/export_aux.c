/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:13:17 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/10 12:26:34 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array_export(t_list *env)
{
	char	**array;
	int		size;
	int		i;
	char	*temp[2];
	t_list	*tmp;
	t_env	*content;

	i = 0;
	tmp = env;
	size = ft_lstsize(env);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	temp[0] = NULL;
	temp[1] = NULL;
	while (i < size)
	{ 
		content = tmp->content;
		if (content->visible)
		{
			temp[0] = ft_strjoin("\"", content->value);
			temp[1] = ft_strjoin(temp[0], "\"");
			free(temp[0]);
			temp[0] = ft_strjoin(content->key, "=");
			array[i] = ft_strjoin(temp[0], temp[1]);
			free(temp[0]);
			free(temp[1]);
		}
		else
			array[i] = ft_strdup("");
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

void swap(char **x, char **y) 
{
	char *temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

void bubble_sort_recursive(char **array, int start, int end) 
{
	if (start >= end)
		return ;
	if (strcmp(array[start], array[start + 1]) > 0) 
	{
		swap(&array[start], &array[start + 1]);
		bubble_sort_recursive(array, start + 1, end);
	}
	bubble_sort_recursive(array, start + 1, end);
}

void bubble_sort(char **array, int size) 
{
	bubble_sort_recursive(array, 0, size - 1);
}

char	**ordenate_envp(t_list *env_lst)
{
	char **array;
	int i = 0;

	array = list_to_array_export(env_lst);
	while (array[i])
		i++;
	bubble_sort(array, i);
	return (array);
}


void	print_export(t_shell *sh)
{
	char **env_ascii;
	int	i = 0;

	env_ascii = ordenate_envp(sh->env_lst);
	while(env_ascii[i])
	{
		if (*env_ascii[i])
			printf("declare -x %s\n", env_ascii[i]);
		i++;
	}
	free_array(env_ascii, i);
}