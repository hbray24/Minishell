/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:33:37 by hbray             #+#    #+#             */
/*   Updated: 2026/04/24 09:52:26 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_pipe(int fd_pipe[2])
{
	if (close(fd_pipe[0]) == -1)
	{
		perror("Minishell :close_pipe");
		if (close(fd_pipe[1]) == -1)
			perror("Minishell :close_pipe");
		exit(1);
	}
	if (close(fd_pipe[1]) == -1)
	{
		perror("Minishell :close_pipe");
		exit(1);
	}
}

int	return_error_fd(void)
{
	if (g_signal_status != 130)
		perror("Minishell :check_fd");
	return (0);
}

int	check_fd(t_ast *ast)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	j = 0;
	i = 0;
	while ((ast->limiter && ast->limiter[j]) || (ast->files && ast->files[i]))
	{
		if (ast->redir[y] == REDIR_OUT)
			ast->fd[1] = open(ast->files[i++], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		else if (ast->redir[y] == REDIR_ADD)
			ast->fd[1] = open(ast->files[i++], O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else if (ast->redir[y] == REDIR_IN)
			ast->fd[0] = open(ast->files[i++], O_RDONLY);
		else if (ast->redir[y] == HERE_DOC)
			ast->fd[0] = here_doc(ast, ast->limiter[j++]);
		if (ast->fd[1] == -1 || ast->fd[0] == -1)
			return (return_error_fd());
		y++;
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
