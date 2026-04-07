/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:37:05 by hbray             #+#    #+#             */
/*   Updated: 2026/04/07 18:34:34 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_ast *ast, t_pipe *p)
{
	if (p->pipes[p->nb_pipe][0] >= 0)
		close(p->pipes[p->nb_pipe][0]);
	if (p->pipes[p->nb_pipe][1] >= 0)
		close(p->pipes[p->nb_pipe][1]);
}

int	exec_cmd(t_ast *ast, t_env *env, t_pipe *p)
{
	if (p->nb_pipe != -1 && p->pipes[p->nb_pipe][0] != -1)
		dup2(p->pipes[p->nb_pipe][0], 1);
	if (p->nb_pipe != -1 && p->pipes[p->nb_pipe][1] != -1)
		dup2(p->pipes[p->nb_pipe][1], 0);
	if (ast->fd[1] != -1)
		dup2(p->pipes[p->nb_pipe][1], 1);
	if (ast->fd[0] != -1)
		dup2(p->pipes[p->nb_pipe][0], 0);
	/*regarde mon repo pipex pour bien comprendre comment fonctionne l'execution des cmds
	tout ca tout ca notamment dup2, execve, comment je vais chercher les cmd etc
	les closes de fd, les forks etc*/
}
