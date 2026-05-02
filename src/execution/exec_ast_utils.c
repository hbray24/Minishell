/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:33:37 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 11:57:43 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	close_pipe(int fd_pipe[2])
{
	if (close(fd_pipe[0]) == -1)
	{
		perror("Minishell :close_pipe");
		if (close(fd_pipe[1]) == -1)
			perror("Minishell :close_pipe");
		return (1);
	}
	if (close(fd_pipe[1]) == -1)
	{
		perror("Minishell :close_pipe");
		return (1);
	}
	return (0);
}

int	return_error_fd(void)
{
	if (g_signal_status != 130)
		perror("Minishell :check_fd");
	return (0);
}

void	check_open_fd(t_ast *ast, t_type type)
{
	if ((type == REDIR_IN || type == HERE_DOC) && ast->fd[0] > -1)
		close(ast->fd[0]);
	if ((type == REDIR_OUT || type == REDIR_ADD) && ast->fd[1] > -1)
		close(ast->fd[1]);
}

int	check_fd(t_ast *ast, t_env *env)
{
	int	i;
	int	y;

	y = -1;
	i = 0;
	while (ast->files && ast->files[i])
	{
		check_open_fd(ast, ast->redir[++y]);
		expander_simple_array(&ast->files[i], env);
		if (ast->redir[y] == REDIR_OUT)
			ast->fd[1] = open(ast->files[i++], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		else if (ast->redir[y] == REDIR_ADD)
			ast->fd[1] = open(ast->files[i++], O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else if (ast->redir[y] == REDIR_IN)
			ast->fd[0] = open(ast->files[i++], O_RDONLY);
		if (ast->fd[1] == -1 || ast->fd[0] == -1)
			return (return_error_fd());
	}
	return (1);
}

void	restore_fd(int origin_stdout_in[2])
{
	dup2(origin_stdout_in[0], 0);
	dup2(origin_stdout_in[1], 1);
	close(origin_stdout_in[0]);
	close(origin_stdout_in[1]);
}
