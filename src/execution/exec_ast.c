/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 19:17:09 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	fork_pipe_child(t_ast *ast, t_env **env, int fd_pipe[2], int direction)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ast->type == PIPE)
			init_ctrl_pipe();
		dup2_child(ast, env, fd_pipe, direction);
		clear_ast((*env)->first_node_ast);
		clear_env(env);
		close_std_fd();
		exit (1);
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
		perror("Minishell :exec_pipe");
		return (1);
	}
	pid_left = fork_pipe_child(ast, env, fd_pipe, LEFT);
	pid_right = fork_pipe_child(ast, env, fd_pipe, RIGHT);
	close_pipe(fd_pipe);
	waitpid(pid_left, &status, 0);
	if (g_signal_status == 130 || g_signal_status == 131)
	{
		free_all(NULL, env, (*env)->first_node_ast);
		close_std_fd();
		exit(g_signal_status);
	}
	waitpid(pid_right, &status, 0);
	return (get_exit_status(status));
}

int	exec_extern(t_ast *ast, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		close(ast->origin_std[0]);
		close(ast->origin_std[1]);
		execve_cmd(ast, env);
		close_std_fd();
	}
	restore_fd(ast->origin_std);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

int	exec_no_fork(t_ast *ast, t_env **env)
{
	int	status;

	if (!check_fd(ast, *env))
		return (1);
	ast->origin_std[0] = dup(0);
	ast->origin_std[1] = dup(1);
	if (!dup_fd(ast))
		return (1);
	if (!expander(ast->token, *env))
		return (restore_fd(ast->origin_std), -1);
	if (!ast->token || !ast->token[0])
		return (restore_fd(ast->origin_std), 0);
	status = exec_build_in(ast, env);
	if (status != -1)
		return (restore_fd(ast->origin_std), status);
	return (exec_extern(ast, env));
}

int	exec_ast(t_ast *ast, t_env **env, int create_fork)
{
	if (!ast)
		return (0);
	if (ast->type == PIPE)
		return (exec_pipe(ast, env));
	if (ast->type == EXEC && !create_fork)
		return (exec_no_fork(ast, env));
	else if (ast->type == EXEC && create_fork)
	{
		if (!check_fd(ast, *env))
			return (free_all(NULL, env, (*env)->first_node_ast), 1);
		if (!dup_fd(ast))
			return (free_all(NULL, env, (*env)->first_node_ast), 1);
		if (!expander(ast->token, *env))
		{
			free_all(NULL, env, (*env)->first_node_ast);
			exit (1);
		}
		if (exec_build_in(ast, env) != -1)
		{
			free_all(NULL, env, (*env)->first_node_ast);
			exit(0);
		}
		execve_cmd(ast, env);
	}
	return (free_all(NULL, env, (*env)->first_node_ast), 1);
}
