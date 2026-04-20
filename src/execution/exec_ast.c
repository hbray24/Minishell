/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/04/20 09:13:19 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int	check_fd(t_ast *ast)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((ast->limiter && ast->limiter[j]) || (ast->files && ast->files[i]))
	{
		if (ast->redir[i] == REDIR_OUT)
			ast->fd[1] = open(ast->files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ast->redir[i] == REDIR_ADD)
			ast->fd[1] = open(ast->files[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (ast->redir[i] == REDIR_IN)
			ast->fd[0] = open(ast->files[i], O_RDONLY);
		if (ast->redir[i] == HERE_DOC)
			ast->fd[0] = here_doc(ast->limiter);
		if (ast->fd[1] == -1 || ast->fd[0] == -1)
		{
			perror("Minishell");
			return (0);
		}
		i++;
		j++;
	}
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

int	dup_fd(t_ast *ast)
{
	if (!check_fd(ast))
		return (0);
	if (ast->fd[1] > -1)
	{
		if (dup2(ast->fd[1], 1) == -1)
		{
			perror("Minishell");
			return (0);
		}
		close(ast->fd[1]);
	}
	if (ast->fd[0] > -1)
	{
		if (dup2(ast->fd[0], 0) == -1)
		{
			perror("Minishell");
			return (0);
		}
		close(ast->fd[0]);
	}
	return (1);
}

int	exec_ast(t_ast *ast, t_env **env, int create_fork)
{
	int		status;
	int		fd_pipe[2];
	pid_t	pid_right;
	pid_t	pid_left;
	pid_t	pid;
	int		origin_stdout_in[2];

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
		{
			signal(SIGQUIT,SIG_DFL);
			signal(SIGINT,SIG_DFL);
			dup2_child(ast, env, fd_pipe, LEFT);
		}
		pid_right = fork();
		if (pid_right == 0)
		{
			signal(SIGQUIT,SIG_DFL);
			signal(SIGINT,SIG_DFL);
			dup2_child(ast, env, fd_pipe, RIGHT);
		}
		close_pipe(fd_pipe);
		waitpid(pid_left, &status, 0);
		waitpid(pid_right, &status, 0);
		return (status);
	}
	if (ast->type == EXEC && !create_fork)
	{
		origin_stdout_in[0] = dup(0);
		origin_stdout_in[1] = dup(1);
		if (!dup_fd(ast))
			return (1);
		status = exec_build_in(ast, env);
		if (status != -1)
		{
			dup2(origin_stdout_in[0], 0);
			dup2(origin_stdout_in[1], 1);
			close(origin_stdout_in[0]);
			close(origin_stdout_in[1]);
			return (status);
		}
		pid = fork();
		if (pid == 0)
		{
			if (!dup_fd(ast))
			 	exit (1);
			signal(SIGQUIT,SIG_DFL);
			signal(SIGINT,SIG_DFL);
			execve_cmd(ast, env);
		}
		close_fd(ast);
		dup2(origin_stdout_in[0], 0);
		dup2(origin_stdout_in[1], 1);
		close(origin_stdout_in[0]);
		close(origin_stdout_in[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				printf("\n");
			else if (WTERMSIG(status) == SIGQUIT)
				printf("Quit (core dumped)\n");
			return(128 + WTERMSIG (status));
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	if (ast->type == EXEC && create_fork)
	{
		if (!dup_fd(ast))
			return (1);
		if (exec_build_in(ast, env) != -1)
			exit (0);
		execve_cmd(ast, env);
	}
	return (1);
}
