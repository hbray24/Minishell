/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:46:23 by hbray             #+#    #+#             */
/*   Updated: 2026/04/01 10:35:52 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* void	execute_pipe(t_ast *ast)
{

} */

int	execute_cmd(t_ast *ast, t_env *env)
{
	int	status;

	status = 1;
	if (ft_strcmp(*ast->token, "cd") == 0)
		status |= ft_cd(ast, env);
	else if (ft_strcmp(*ast->token, "pwd") == 0)
		status |= ft_pwd();
	else if (ft_strcmp(*ast->token, "env") == 0)
		ft_env(&env);
	else if (ft_strcmp(*ast->token, "exit") == 0)
		return (0);
	return (status);
}

int	execute_ast(t_ast *ast, t_env *env)
{
	int	status;

	status = 0;
	if (!ast)
		return (0);
	// if (ast->type == PIPE)
	// 	execute_pipe(ast);
	else if (ast->type == EXEC)
		status = execute_cmd(ast, env);
	return (status);
}

