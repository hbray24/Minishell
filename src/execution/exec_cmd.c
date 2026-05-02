/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:37:05 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 18:44:04 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**fill_env_array(char **build_env, t_env *start)
{
	char	*tmp;
	int		i;

	i = 0;
	while (start)
	{
		if (start->value)
		{
			tmp = ft_strjoin(start->key, "=");
			if (tmp)
				build_env[i] = ft_strjoin(tmp, start->value);
			free(tmp);
			if (!tmp || !build_env[i++])
			{
				perror("Minishell :fill_env_array");
				free_array(build_env);
				return (NULL);
			}
		}
		start = start->next;
	}
	return (build_env);
}

char	**linked_list_to_double_array(t_env **envp)
{
	char	**build_env;
	int		i;
	t_env	*start;

	free_array((*envp)->env);
	start = *envp;
	i = 0;
	while (start)
	{
		start = start->next;
		i++;
	}
	build_env = ft_calloc(i + 1, sizeof(char *));
	if (!build_env)
	{
		perror("Minishell :linked_list_to_double_array");
		return (NULL);
	}
	start = *envp;
	i = 0;
	build_env[i] = NULL;
	return (fill_env_array(build_env, *envp));
}

int	exec_build_in(t_ast *ast, t_env **env)
{
	int	status;

	status = 0;
	if (!ft_strcmp(*ast->token, "cd"))
		status |= ft_cd(ast, *env);
	else if (!ft_strcmp(*ast->token, "pwd"))
		status |= ft_pwd();
	else if (!ft_strcmp(*ast->token, "env"))
		status |= ft_env(ast, env);
	else if (!ft_strcmp(*ast->token, "export"))
		status |= ft_export(ast, env);
	else if (!ft_strcmp(*ast->token, "unset"))
		ft_unset(ast, env);
	else if (!ft_strcmp(*ast->token, "echo"))
		ft_echo(ast);
	else if (!ft_strcmp(*ast->token, "exit"))
		status |= ft_exit(ast, *env);
	else
		return (-1);
	close_std_fd();
	return (status);
}

void	exit_cmd(t_env **env, int status)
{
	free_all(NULL, env, (*env)->first_node_ast);
	close_std_fd();
	exit (status);
}

int	execve_cmd(t_ast *ast, t_env **env)
{
	char	*path;

	if (ast->token[0] && !ast->token[0][0])
		exit_cmd(env, 0);
	(*env)->env = linked_list_to_double_array(env);
	if (!(*env)->env)
		exit_cmd(env, 1);
	path = find_cmd_path(ast->token[0], (*env)->env);
	if (path == NULL)
	{
		write(2, "Minishell: Cmd not found\n", 26);
		free_array((*env)->env);
		exit_cmd(env, 127);
	}
	execve(path, ast->token, (*env)->env);
	free_array((*env)->env);
	free_all(NULL, env, (*env)->first_node_ast);
	close_std_fd();
	free(path);
	exit (126);
}
