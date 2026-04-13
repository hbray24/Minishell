/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/04/13 20:06:57 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int	exec_build_in(t_ast *ast, t_env **env)
{
	int	status;

	status = 0;
	if (!ft_strcmp(*ast->token, "cd"))
		status |= ft_cd(ast, *env);
	else if (!ft_strcmp(*ast->token, "pwd"))
		status |= ft_pwd();
	else if (!ft_strcmp(*ast->token, "env"))
		ft_env(env);
	else if (!ft_strcmp(*ast->token, "export"))
		ft_export(ast, env);
	else if (!ft_strcmp(*ast->token, "unset"))
		ft_unset(ast, env);
	else if (!ft_strcmp(*ast->token, "echo"))
		ft_echo(ast);
	else if (!ft_strcmp(*ast->token, "exit"))
		status |= ft_exit(ast, *env);
	else
		return(-1);
	return (status);
}

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
		pipe(fd_pipe);
		pid_left = fork();
		if (pid_left == 0)
		{
			dup2(fd_pipe[1], 1);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			exec_ast(ast->l_child, env, 1);
			exit (1);
		}
		pid_right = fork();
		if (pid_right == 0)
		{
			dup2(fd_pipe[0], 0);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			exec_ast(ast->r_child, env, 1);
			exit (1);
		}
		close(fd_pipe[0]);
		close(fd_pipe[1]);
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
