/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:42:57 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 17:05:46 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	dup_fd(t_ast *ast)
{
	if (ast->fd[1] > -1)
	{
		if (dup2(ast->fd[1], 1) == -1)
		{
			perror("Minishell :dup_fd");
			return (0);
		}
		close(ast->fd[1]);
		ast->fd[1] = -1;
	}
	if (ast->fd[0] > -1)
	{
		if (dup2(ast->fd[0], 0) == -1)
		{
			perror("Minishell :dup_fd");
			return (0);
		}
		close(ast->fd[0]);
		ast->fd[0] = -1;
	}
	return (1);
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	dup2_child(t_ast *ast, t_env **env, int fd_pipe[2], int direction)
{
	if (direction == LEFT)
	{
		if (dup2(fd_pipe[1], 1) == -1)
		{
			perror("Minishell: dup2");
			return (1);
		}
		if (close_pipe(fd_pipe))
			return (1);
		exec_ast(ast->l_child, env, 1);
		return (1);
	}
	else
	{
		if (dup2(fd_pipe[0], 0) == -1)
		{
			perror("Minishell: dup2");
			return (2);
		}
		if (close_pipe(fd_pipe))
			return (2);
		exec_ast(ast->r_child, env, 1);
		return (2);
	}
	return (0);
}
