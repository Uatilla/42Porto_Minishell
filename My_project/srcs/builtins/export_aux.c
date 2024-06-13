/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:13:17 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/12 10:21:06 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **x, char **y)
{
	char	*temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void	bubble_sort_recursive(char **array, int size)
{
	int	i;

	i = 0;
	if (size == 1)
		return ;
	while (i < size - 1)
	{
		if (ft_strcmp(array[i], array[i + 1]) > 0)
			swap(&array[i], &array[i + 1]);
		i++;
	}
	bubble_sort_recursive(array, size - 1);
}

void	bubble_sort(char **array, int size)
{
	bubble_sort_recursive(array, size);
}

char	**ordenate_envp(t_list *env_lst)
{
	char	**array;
	int		i;

	i = 0;
	array = list_to_array_export(env_lst);
	while (array[i])
		i++;
	bubble_sort(array, i);
	return (array);
}

void	print_export(t_shell *sh)
{
	char	**env_ascii;
	int		i;

	i = 0;
	env_ascii = ordenate_envp(sh->env_lst);
	while (env_ascii[i])
	{
		if (*env_ascii[i])
			printf("declare -x %s\n", env_ascii[i]);
		i++;
	}
	free_array(env_ascii, i);
}
