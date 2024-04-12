/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/04/11 19:57:06 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_var (char **env_var)
{
    int i;

    i = 0;
    while (env_var[i])
        i++;
    return (i);
}
/*Return the environment variables as a linked list.*/
void    fill_env(t_shell *sh, char **env_var)
{
    int i;

    i = 0;
    while(*env_var)
    {
       //Split the content of the current *env_var
       //Create a new node
            //Set the content into the node.
                //node[0] = Key
                //node[1] = Variable
                //visible = true
        //add the current to end of the list
        env_var++;
    }
}

void    init_shell(t_shell *sh, char **env_var)
{
    /*0) Set t_shell struct as 0.*/
    ft_bzero(sh, sizeof(t_shell));
    /*1) Put each *env into the structure
    Remember to set the visibility var as true*/
    fill_env(sh, env_var);
    
}

int main(int argc, char **argv, char **envp)
{
    t_shell    sh;

    init_shell(&sh, envp);
    printf("ARGC: %d \t %s\n", argc, argv[1]);
    while (*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }

    return (0);
}
