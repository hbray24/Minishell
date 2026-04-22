/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:33:37 by hbray             #+#    #+#             */
/*   Updated: 2026/04/22 11:25:12 by asauvage         ###   ########.fr       */
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
	int	y;

	y = 0;
	j = 0;
	i = 0;
	while ((ast->limiter && ast->limiter[j]) || (ast->files
			&& ast->files[i]))
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
			ast->fd[0] = here_doc(ast->limiter[j++]);
		if (ast->fd[1] == -1 || ast->fd[0] == -1)
		{
			perror("Minishell");
			return (0);
		}
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
