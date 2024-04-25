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

bool    only_white(char *input, int curr_pos)
{
    while (input[curr_pos])
    {
        if (ft_iswhitespace(input[curr_pos]))
            curr_pos++;
        else 
            return (false);
    }
    return (true);
}
bool    is_a_pipe(char c)
{
    return (c == '|');
}

bool    is_a_bigger(char c)
{
    return (c == '>');
}

bool    is_a_smaller(char c)
{
    return (c == '<');
}

bool    sintax_validation(char *input)
{
    int i;
    bool    fst_wrd;
    char    *temp;

    temp = ft_strtrim(input, " \t");
    i = 0;
    fst_wrd = true;
    while (input[i])
    {
        while (ft_iswhitespace(input[i]))
            i++;
        if (fst_wrd == true && is_a_pipe(input[i]))
        {
            fst_wrd = false;
            ft_printf("bash: syntax error near unexpected token `|'\n");
            return (false);
        }

        if (is_a_bigger(input[i]))
        {
            if ((only_white(input, i + 1)) || (is_a_bigger(input[i + 1]) && \
                (is_a_bigger(input[i + 2]) || only_white(input, i + 2))))
                {
                    ft_printf("bash: syntax error near unexpected token `newline'\n");
                    return (false);
                }
            else if (is_a_pipe(input[i + 1]) || ((is_a_bigger(input[i + 1]) && is_a_pipe(input [i + 2]))))
                {
                    ft_printf("bash: syntax error near unexpected token `|'\n");
                    return (false);
                }
        }
        else if (is_a_smaller(input[i]))
        {
            if ((only_white(input, i + 1)) || (is_a_smaller(input[i + 1]) && \
                (is_a_smaller(input[i + 2]) || only_white(input, i + 2))))
                {
                    ft_printf("bash: syntax error near unexpected token `newline'\n");
                    return (false);
                }
            else if (is_a_pipe(input[i + 1]) || ((is_a_smaller(input[i + 1]) && is_a_pipe(input [i + 2]))))
                {
                    ft_printf("bash: syntax error near unexpected token `|'\n");
                    return (false);
                }
        }
        else if (is_a_pipe(input[i]))
        {
            if (is_a_bigger(input [i + 1]) || is_a_smaller(input [i + 1]))
            {
                ft_printf("bash: syntax error near unexpected token `|'\n");
                    return (false);
            }
        }
        i++;
    }
    return (true);
}