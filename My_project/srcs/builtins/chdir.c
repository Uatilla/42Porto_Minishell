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

void	cd_others(t_shell *sh, char *dest_folder)
{
	int		ret;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	ret = 0;
	getcwd(old_pwd, sizeof(old_pwd));
	ret = chdir(dest_folder);
	if (ret)
	{
		perror(dest_folder);
		g_signo = 1;
	}
	else
	{
		att_env(sh, "OLDPWD", old_pwd);
		att_env(sh, "HOME", getcwd(new_pwd, sizeof(new_pwd)));
	}
}

void	cd_home(t_shell *sh)
{
	char	*home_path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	home_path = get_env(sh->env_lst, "HOME");
	if (home_path)
	{
		getcwd(old_pwd, sizeof(old_pwd));
		g_signo = chdir(home_path);
		if (g_signo != 0)
			printf("Error in changing directory\n"); //PUT THIS INTO FD2.
		else
		{
			att_env(sh, "OLDPWD", old_pwd);
			att_env(sh, "HOME", getcwd(new_pwd, sizeof(new_pwd)));
		}
	}
	else
		printf("Minishell: cd: HOME not set\n"); //PUT THIS INTO FD2.
	free(home_path);
}

void	exec_cd(t_shell *sh, char **argv)
{
	if ((!argv[1]))
		cd_home(sh);
	else
		cd_others(sh, argv[1]);
}

int	change_dir(t_shell *sh, t_execcmd *cmd)
{
	(void)sh;
	g_signo = 0;
	if (!sintax_valid_cd(cmd->argv[0], cmd->argv, sh))
		g_signo = 1;
	else
		exec_cd(sh, cmd->argv);
	return (g_signo);
}
