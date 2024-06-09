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

bool    check_option(char *input)
{
    while (*input)
    {
        if (*input == '-')
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
    
    //Check if there is not argv[1]
    if (!argv[1])
        return (true);

    //count how many args we have, returns if more than 2 args
    argc = 0;
    while (argv[argc])
    {
        if (argc > 1)
            return (false);
        argc++;
    }
    //look for more than 2 dots in sequence.
    if (!check_dots(argv[1]) || !check_option(argv[1]))
        return (false);
    return (true);
}

void    cd_others(char *dest_folder)
{
    g_signo = chdir(dest_folder);
    if (g_signo != 0)
    {
        printf("error\n");
        g_signo = 1;
    }
}

void    cd_home(t_shell *sh)
{
    //char    str[PATH_MAX];
    char    *value;

    value = get_env(sh->env_lst, "HOME");
    if (value)
    {
        g_signo = chdir(value);
        if (g_signo != 0)
            printf("Error in changing directory\n"); //PUT THIS INTO FD2.
    }
    else
        printf("Minishell: cd: HOME not set\n"); //PUT THIS INTO FD2.
}

void    exec_cd(t_shell *sh, char **argv)
{
    if ((!argv[1]))
        cd_home(sh);
    else
        cd_others(argv[1]);
}

void    chg_dir(t_shell *sh)
{
    char **argv;
    int     i;
    
    (void)sh;
    //allocating memory to use in the structure
    i = 0;
    argv = ft_calloc(4, sizeof(char **));
    if (!argv)
        return ;
    argv[2] = 0;

    //adding information into the structure.
    argv[0] = "cd";
    //argv[1] = NULL;
    argv[1] = "../../../";
  

    //Analysis of syntax
    if (!sintax_valid_cd(argv[0], argv, sh))
        exit(1);
        //clear_exit(sh, 1);
    
    exec_cd(sh, argv);
    
    

}
