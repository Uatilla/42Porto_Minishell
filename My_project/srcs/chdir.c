/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:31:02 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/08 19:31:07 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    check_dots(char *input)
{
    int count;

    count = 0;
    while (*input)
    {
        if (*input == '.')
            count++;
        else
            count = 0;
        if(count >= 3)
            return (false);
        input++;
    }
    return (true);
}

bool    sintax_valid_cd(char *cmd, char **argv, t_shell *sh)
{
    int argc;

    (void)sh;
    (void)cmd;
    
    if (!argv[1])
        return (false);
    //count how many args we have.
    argc = 0;
    while (argv[argc])
    {
        if (argc > 1)
            return (false);
        argc++;
    }
    //look for more than 2 dots in sequence.
    if (!check_dots(argv[1]))
        return (false);
    return (true);
}

/*void    token_cd_lst(char *input, t_shell *sh)
{
    t_cd    *cd_node;
    char    *sep;

    input++;
    while (*input)
    {
        sep = ft_strchr(*input, '/');
        if (sep)
        {

        }
        input++;
    }
}*/

void    chg_dir(t_shell *sh)
{
    char **argv;
    char **input_splitted;
    int     i;
    (void)sh;
    //allocating memory to use in the structure
    i = 0;
    argv = ft_calloc(4, sizeof(char **));
    if (!argv)
        return ;
    argv[3] = 0;

    //adding information into the structure.
    argv[0] = "cd";
    //argv[1] = NULL;
    argv[1] = "../../../Documents/";
    //printf("Cmd: [%s], Arg: [%s]\n", argv[0], argv[1]);
    if (!sintax_valid_cd(argv[0], argv, sh))
        exit(1);
        //clear_exit(sh, 1);

    //Tokenize cd input
    //token_cd_lst(argv[1], sh);
    input_splitted = ft_split(argv[1], '/');
    i = 0;
    while (input_splitted[i])
    {
        printf("[%d] %s\n", i, input_splitted[i]);
        i++;
    }
    
    

}
