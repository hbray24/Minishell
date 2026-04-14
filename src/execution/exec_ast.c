/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/04/14 15:43:48 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int	check_fd(t_ast *ast)
{
	int	i;

	i = 0;
	while (ast->files && ast->files[i])
	{
		if (ast->redir[i] == REDIR_OUT)
			ast->fd[1] = open(ast->files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (ast->redir[i] == REDIR_ADD)
			ast->fd[1] = open(ast->files[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (ast->redir[i] == REDIR_IN)
			ast->fd[0] = open(ast->files[i], O_RDONLY);
		// else if (ast->redir[i] == HERE_DOC) c'est pour le here_doc pas sur de savoir si je fais avec un file ou un pipe
			// ast->fd[0] = 
		if (ast->fd[1] == -1 || ast->fd[0] == -1)
		{
			perror("hbray:");
			return (0);
		}
		i++;
	}
	if (!ast->fd[0])
		ast->fd[0] = -1;
	if (!ast->fd[1])
		ast->fd[1] = -1;
	return (1);
}

void	close_pipe(int fd_pipe[2])
{
	if (close(fd_pipe[0]) == -1)
	{
		perror("Minishell");
		if (close(fd_pipe[1]) == -1)
			perror("Minishell");
		exit (1);
	}
	if (close(fd_pipe[1]) == -1)
	{
		perror("Minishell");
		exit (1);
	}
}

int	dup2_child(t_ast *ast, t_env ** env, int fd_pipe[2], int direction)
{
	if (direction == LEFT)
	{
		if(dup2(fd_pipe[1], 1) == -1)
		{
			perror("dup2");
			exit (1);
		}
		close_pipe(fd_pipe);
		exec_ast(ast->l_child, env, 1);
		exit (1);
	}
	else
	{
		if(dup2(fd_pipe[0], 0) == -1)
		{
			perror("dup2");
			exit (1);
		}
		close_pipe(fd_pipe);
		exec_ast(ast->r_child, env, 1);
		exit (1);
	}
	exit (1);
}

int	exec_ast(t_ast *ast, t_env **env, int create_fork)
{
	int		status;
	int		fd_pipe[2];
	pid_t	pid_right;
	pid_t	pid_left;
	pid_t	pid;

	if (!ast)
		return (0);
	else if (ast->type == PIPE)
	{
		if (pipe(fd_pipe) == -1)
		{
			perror("Minishell");
			return (1);
		}
		pid_left = fork();
		if (pid_left == 0)
			dup2_child(ast, env, fd_pipe, LEFT);
		pid_right = fork();
		if (pid_right == 0)
			dup2_child(ast, env, fd_pipe, RIGHT);
		close_pipe(fd_pipe);
		waitpid(pid_left, &status, 0);
		waitpid(pid_right, &status, 0);
		return (status);
	}
	if (ast->type == EXEC && !create_fork)
	{
		status = exec_build_in(ast, env);
		if (status != -1)
			return (status);
		pid = fork();
		if (pid == 0)
			execve_cmd(ast, env);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	if (ast->type == EXEC && create_fork)
	{
		check_fd(ast);
		if (exec_build_in(ast, env) != -1)
			exit (0);
		execve_cmd(ast, env);
	}
	return (1);
}
