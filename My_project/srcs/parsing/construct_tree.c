/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:35:14 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/11 21:46:14 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_execcmd(t_shell *sh, t_execcmd *cmd, char *arg)
{
	int	argc;

	argc = 0;
	while (cmd->argv[argc])
		argc++;
	cmd->argv[argc] = ft_strdup(arg);
	if (!cmd->argv[argc])
		clear_exit(sh, 1);
	if (argc == 0)
		cmd->command = find_path(sh, cmd->argv[0]);
}

/*Construct the exec structure.*/
t_cmd	*execcmd(t_shell *sh, t_list *tkn_pos)
{
	t_execcmd	*cmd;
	int			num_args;

	(void)sh;
	cmd = malloc(sizeof(t_execcmd));
	if (!cmd)
		clear_exit(sh, 1);
	ft_memset(cmd, 0, sizeof(t_execcmd));
	cmd->n_type = N_EXEC;
	cmd->curr_tkn_pos = tkn_pos;
	num_args = count_args(sh, tkn_pos);
	cmd->argv = ft_calloc(num_args + 1, sizeof(char *));
	if (!cmd->argv)
		clear_exit(sh, 1);
	cmd->command = NULL;
	return ((t_cmd *)cmd);
}

t_cmd	*get_redir(t_cmd *cmd)
{
	t_redircmd	*redircmd;

	while (cmd->n_type == N_REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		if ((redircmd->cmd)->n_type == N_EXEC)
			break ;
		else
			cmd = redircmd->cmd;
	}
	return (cmd);
}

/*Construct the Redir node and updates the pointer*/
t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redircmd	*cmd;
	t_cmd		*old_rd_valid;

	cmd = malloc(sizeof(t_redircmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_redircmd));
	cmd->n_type = N_REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	if (fd == 0)
		cmd->perm = 0444;
	else
		cmd->perm = 0644;
	cmd->curr_tkn_pos = subcmd->curr_tkn_pos;
	if (subcmd->n_type != N_EXEC)
	{
		old_rd_valid = get_redir((t_cmd *)cmd);
		cmd->cmd = ((t_redircmd *)old_rd_valid)->cmd;
		((t_redircmd *)(old_rd_valid))->cmd = (t_cmd *)cmd;
		return (subcmd);
	}
	return ((t_cmd *)cmd);
}

/*Construct the pipe node and pointers it to the right and left side.
Updates the pointer.*/
t_cmd	*pipecmd(t_shell *sh, t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_pipecmd));
	if (!cmd)
		clear_exit(sh, 1);
	ft_memset(cmd, 0, sizeof(t_pipecmd));
	cmd->n_type = N_PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
