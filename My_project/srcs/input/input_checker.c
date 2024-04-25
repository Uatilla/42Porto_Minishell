/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:32:43 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/18 20:32:47 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    input_check(int argc, char **argv, char **envp)
{
    if (argc != 1 || argv[1])
    {
        ft_putstr_fd("ERROR: MINISHELL can't receive inputs.\n", 2);
        clear_exit(NULL, 1);
    }
    if (!envp[0])
    {
        ft_putstr_fd("ERROR: ENVIRONMENT VARIABLES are empty\n", 2);
    }
}

/*bool    sintax_validation(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '|')
            check_pipe(input, i);
        i++;
    }
    return (true);
}*/