/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/04/22 10:52:06 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	fork_pipe_child(t_ast *ast, t_env **env, int fd_pipe[2], int direction)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		dup2_child(ast, env, fd_pipe, direction);
	}
	return (pid);
}

int	exec_pipe(t_ast *ast, t_env **env)
{
	int		status;
	int		fd_pipe[2];
	pid_t	pid_right;
	pid_t	pid_left;

	if (pipe(fd_pipe) == -1)
	{
		perror("Minishell");
		return (1);
	}
	pid_left = fork_pipe_child(ast, env, fd_pipe, LEFT);
	pid_right = fork_pipe_child(ast, env, fd_pipe, RIGHT);
	close_pipe(fd_pipe);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (get_exit_status(status));
}

int	exec_extern(t_ast *ast, t_env **env, int origin_stdout_in[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve_cmd(ast, env);
	}
	close_fd(ast);
	restore_fd(origin_stdout_in);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

int	exec_no_fork(t_ast *ast, t_env **env)
{
	int	status;
	int	origin_stdout_in[2];

	origin_stdout_in[0] = dup(0);
	origin_stdout_in[1] = dup(1);
	if (!dup_fd(ast))
		return (1);
	if (!ast->token || !ast->token[0])
	{
		restore_fd(origin_stdout_in);
		return (0);
	}
	status = exec_build_in(ast, env);
	if (status != -1)
	{
		restore_fd(origin_stdout_in);
		return (status);
	}
	return (exec_extern(ast, env, origin_stdout_in));
}

int	exec_ast(t_ast *ast, t_env **env, int create_fork)
{
	if (!ast)
		return (0);
	else if (ast->type == PIPE)
		return (exec_pipe(ast, env));
	else if (ast->type == EXEC && !create_fork)
		return (exec_no_fork(ast, env));
	else if (ast->type == EXEC && create_fork)
	{
		if (!dup_fd(ast))
			return (1);
		if (exec_build_in(ast, env) != -1)
			exit(0);
		execve_cmd(ast, env);
	}
	return (1);
}
