/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:10:12 by hbray             #+#    #+#             */
/*   Updated: 2026/04/23 11:10:29 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*search_old_path(t_env *env)
{
	char	*path;
	char	*env_pwd;

	path = getcwd(NULL, 0);
	if (!path)
	{
		env_pwd = search_value("PWD", env);
		if (env_pwd)
		{
			path = ft_strdup(env_pwd);
			if (!path)
			{
				perror("Minishell :search_old_path");
				return (NULL);
			}
		}
		else
			return (NULL);
	}
	return (path);
}

char	*search_new_path(t_ast *ast, char *old_path)
{
	char	*path;
	char	*tmp_path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("Minishell :search_new_path");
		tmp_path = ft_strjoin(old_path, "/");
		path = ft_strjoin(tmp_path, ast->token[1]);
		free(tmp_path);
	}
	return (path);
}
