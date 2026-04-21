/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:10:12 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 11:35:23 by hbray            ###   ########.fr       */
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
				perror("Minishell");
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
		perror("cd :");
		tmp_path = ft_strjoin(old_path, "/");
		path = ft_strjoin(tmp_path, ast->token[1]);
		free(tmp_path);
	}
	return (path);
}
