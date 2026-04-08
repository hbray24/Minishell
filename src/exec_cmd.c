/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:37:05 by hbray             #+#    #+#             */
/*   Updated: 2026/04/08 16:54:50 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_ast *ast, t_pipe *p)
{
	if (p->pipes && p->pipes[p->nb_pipe][0] >= 0)
		close(p->pipes[p->nb_pipe][0]);
	if (p->pipes && p->pipes[p->nb_pipe][1] >= 0)
		close(p->pipes[p->nb_pipe][1]);
	if (ast->fd[0])
		close(ast->fd[0]);
	if (ast->fd[1])
		close(ast->fd[1]);
}

char	**linked_list_to_double_array(t_env **envp)
{
	char	**build_env;
	char	*tmp;
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
	build_env = malloc(sizeof(char) * (i + 1));
	if (!build_env)
		return (NULL);
	start = *envp;
	i = 0;
	while (start)
	{
		if (start->value)
		{
			tmp = ft_strjoin(start->key, "=");
			if (!tmp)
			{
				free(tmp);
				return (NULL);
			}
			build_env[i] = ft_strjoin(tmp, start->value);
			free(tmp);
			if (!build_env[i++])
			{
				free_array(build_env);
				return (NULL);
			}
		}
		start = start->next;
	}
	build_env[i] = NULL;
	return (build_env);
}

int	exec_cmd(t_ast *ast, t_env **env, t_pipe *p)
{
	char	*path;

	if (p->nb_pipe != -1 && p->pipes[p->nb_pipe][0] != -1)
		dup2(p->pipes[p->nb_pipe][0], 1);
	if (p->nb_pipe != -1 && p->pipes[p->nb_pipe][1] != -1)
		dup2(p->pipes[p->nb_pipe][1], 0);
	if (ast->fd[1] != -1)
		dup2(p->pipes[p->nb_pipe][1], 1);
	if (ast->fd[0] != -1)
		dup2(p->pipes[p->nb_pipe][0], 0);
	close_fd(ast, p);
	(*env)->env = linked_list_to_double_array(env);
	path = find_cmd_path(ast->token[0], (*env)->env);
	if (path == NULL)
	{
		write(2, "hbray: Cmd not found\n", 21);
		exit(127);
	}
	execve(path, ast->token, (*env)->env);
	exit (1);
}
