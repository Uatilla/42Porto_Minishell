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

bool    check_bigger(char *input, int i)
{
    if ((only_white(input, i + 1)) || is_a_pipe(input [i + 1]) || (is_a_bigger(input[i + 1]) && \
        only_white(input, i + 2)))
        {
            ft_printf("bash: syntax error near unexpected token `newline'\n");
            return (false);
        }
    else if (is_a_bigger(input [i + 1]) && is_a_bigger(input [i + 2]))
        {
            ft_printf("bash: syntax error near unexpected token `>'\n");
            return (false);
        }
    else if (is_a_smaller(input [i + 1]))
        {
            ft_printf("bash: syntax error near unexpected token `<'\n");
            return (false);
        }
    else if (((is_a_bigger(input[i + 1]) && is_a_pipe(input [i + 2]))))
        {
            ft_printf("bash: syntax error near unexpected token `|'\n");
            return (false);
        }
    return (true);
}

bool    check_smaller(char *input, int i)
{
    if ((only_white(input, i + 1)) || (is_a_smaller(input[i + 1]) && \
    (is_a_smaller(input[i + 2]) || only_white(input, i + 2))))
    {
        ft_printf("bash: syntax error near unexpected token `newline'\n");
        return (false);
    }
    else if (is_a_bigger(input [i + 1]) && only_white(input, i + 2))
    {
        ft_printf("bash: syntax error near unexpected token `newline'\n");
        return (false);
    }
    else if (is_a_pipe(input[i + 1]) || ((is_a_smaller(input[i + 1]) && is_a_pipe(input [i + 2]))))
    {
        ft_printf("bash: syntax error near unexpected token `|'\n");
        return (false);
    }
    return (true);
}

bool    spc_char_check(char *input, int i)
{
    if (is_a_bigger(input[i]))
    {
        if (!check_bigger(input, i))
            return (false);
    }
    else if (is_a_smaller(input[i]))
    {
        if (!check_smaller(input, i))
            return (false);
    }
    else if (is_a_pipe(input[i]))
    {
        if (is_a_bigger(input [i + 1]) || is_a_smaller(input [i + 1]))
        {
            ft_printf("bash: syntax error near unexpected token `|'\n");
                return (false);
        }
    }
    return (true);
}

int     search_c_quote(char *input, int i, char search)
{
    while (input[++i])
    {
        if (input[i] == search)
            return (i);
        
    }
    ft_printf("ERROR\n");
    return (i);
}

bool    sintax_validation(char *input)
{
    int i;
    bool    fst_wrd;
    bool    in_quotes;

    i = 0;
    fst_wrd = true;
    in_quotes = false;
    while (input[i])
    {
        
        if (input[i] == '\'' || input[i] == '\"')
        {
            fst_wrd = false;
            i = search_c_quote(input, i, input[i]);
            if (!input[i])
                return (false); // Quote error
        }
        while (ft_iswhitespace(input[i]))
            i++;
        if (fst_wrd == true && is_a_pipe(input[i]))
        {
            fst_wrd = false;
            ft_printf("bash: syntax error near unexpected token `|'\n");
            return (false); // Return error flow.
        }
        if (is_a_bigger(input [i]) || is_a_smaller(input [i])  || is_a_pipe(input [i]))
        {
            fst_wrd = false;
            if (!spc_char_check(input, i))
                return (false);
        }
        else
            fst_wrd = false;

        i++;
    }
    return (true);
}