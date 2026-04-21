/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:33:37 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 11:36:30 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_pipe(int fd_pipe[2])
{
	if (close(fd_pipe[0]) == -1)
	{
		perror("Minishell");
		if (close(fd_pipe[1]) == -1)
			perror("Minishell");
		exit(1);
	}
	if (close(fd_pipe[1]) == -1)
	{
		perror("Minishell");
		exit(1);
	}
}

int	check_fd(t_ast *ast)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while ((ast->limiter && ast->limiter[++j]) || (ast->files
			&& ast->files[++i]))
	{
		if (ast->redir[i] == REDIR_OUT)
			ast->fd[1] = open(ast->files[i], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		if (ast->redir[i] == REDIR_ADD)
			ast->fd[1] = open(ast->files[i], O_CREAT | O_WRONLY | O_APPEND,
					0644);
		if (ast->redir[i] == REDIR_IN)
			ast->fd[0] = open(ast->files[i], O_RDONLY);
		if (ast->redir[i] == HERE_DOC)
			ast->fd[0] = here_doc(ast->limiter);
		if (ast->fd[1] == -1 || ast->fd[0] == -1)
		{
			perror("Minishell");
			return (0);
		}
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
