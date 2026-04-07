/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:37:05 by hbray             #+#    #+#             */
/*   Updated: 2026/04/07 14:45:08 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_ast *ast, t_env *env, t_pipe *p)
{
	if (p->nb_pipe)
	{
		if (p->pipes[p->nb_pipe][0] != -1)
			dup2(p->pipes[p->nb_pipe][0], 1);
		if (p->pipes[p->nb_pipe][1] != -1)
			dup2(p->pipes[p->nb_pipe][1], 0);
		if (ast->fd)
	}
}
