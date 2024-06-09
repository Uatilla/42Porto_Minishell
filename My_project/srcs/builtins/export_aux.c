/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:13:17 by lebarbos          #+#    #+#             */
/*   Updated: 2024/06/09 21:15:58 by lebarbos         ###   ########.fr       */
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
	array = (char **)malloc(sizeof(char *) * size);
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

char	**ordenate_envp(t_list *env_lst)
{
	char **array;
	
	array = list_to_array_export(env_lst);
	
	return (array);
}


void	print_export(t_shell *sh)
{
	char **env_ascii;
	// int	i;

	env_ascii = ordenate_envp(sh->env_lst);
	// while(env_ascii[i++])
	// 	printf("%s\n", env_ascii);
}