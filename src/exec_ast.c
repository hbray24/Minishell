/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/04/07 15:38:22 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int	execute_cmd(t_ast *ast, t_env *env, t_pipe *pipes)
{
	int	status;

	(void)pipes;
	status = 1;
	if (!ft_strcmp(*ast->token, "cd"))
		status |= ft_cd(ast, env);
	else if (!ft_strcmp(*ast->token, "pwd"))
		status |= ft_pwd();
	else if (!ft_strcmp(*ast->token, "env"))
		ft_env(&env);
	else if (!ft_strcmp(*ast->token, "export"))
		ft_export(ast, &env);
	else if (!ft_strcmp(*ast->token, "unset"))
		ft_unset(ast, &env);
	else if (!ft_strcmp(*ast->token, "echo"))
		ft_echo(ast);
	else if (!ft_strcmp(*ast->token, "exit"))
		status |= ft_exit(ast, env);
	// else
	// 	status = exec_cmd(ast, env, pipe);
	return (status);
}

// int	malloc_pipe(t_ast *ast, t_pipe *pipe)
// {
// 	if (ast->type == PIPE)
// 	{
// 		pipe->nb_pipe++;
// 		malloc_pipe(ast->l_child, pipe);
// 		malloc_pipe(ast->r_child, pipe);
// 		pipe->pipes = malloc(sizeof(int[2]) * (pipe->nb_pipe));
// 		if (!pipe->pipes)
// 			return (0);
// 		return (1);
// 	}
// 	return (1);
// }

// int	check_ast(t_ast *ast)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	while (ast->files[i])
// 	{
// 		if (ast->redir[i] == )
// 	}
// }

int	execute_ast(t_ast *ast, t_env *env, t_pipe *pipes, int start_pipe)
{
	int		status;
	// pid_t	pid;

	(void)start_pipe;
	status = 0;
	if (!ast)
		return (0);
	// if (ast->type == PIPE)
	// {
	// 	execute_ast(ast->l_child, env, pipe, start_pipe);
	// 	execute_ast(ast->r_child, env, pipe, start_pipe);
	// }
	if (ast->type == EXEC)
	{
		// if (pipes->nb_pipe)
		// {
		// 	if (pipe(pipes->pipes[pipes->nb_pipe - 1]) == -1)
		// 		return (1);
		// 	if (start_pipe == pipes->nb_pipe)
		// 		pipes->pipes[pipes->nb_pipe - 1][0] = -1;
		// 	pipes->nb_pipe--;
		// }
		// check_fd(ast);
		// pid = fork();
		// if (pid == 0)
		status = execute_cmd(ast, env, pipes);
		// waitpid(pid, &status, 0);
	}
	return (status);
}
