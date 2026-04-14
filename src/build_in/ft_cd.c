/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:29:31 by hbray             #+#    #+#             */
/*   Updated: 2026/04/14 14:25:20 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_to_home(t_ast *ast, t_env *env)
{
	char	*home;
	char	*path;

	home = search_value("HOME", env);
	if (!home)
	{
		write(2, "Didn't find HOME in env\n", 25);
		return (0);
	}
	path = ft_strjoin(home, &ast->token[1][1]);
	if (!path)
	{
		write(2, "Error: Malloc failed\n", 22);
		return (0);
	}
	free(ast->token[1]);
	ast->token[1] = path;
	return (1);
}

int	ft_cd_basic(t_ast *ast, t_env *env, char *old_path)
{
	char	*new_path;
	char	*tmp_path;

	if (ast->token[1][0] == '~')
	{
		if (!join_to_home(ast, env))
			return (1);
	}
	if (chdir(ast->token[1]) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (1);
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("cd :");
		tmp_path = ft_strjoin(old_path, "/");
		new_path = ft_strjoin(tmp_path, ast->token[1]);
		free(tmp_path);
	}
	uptade_env(&env, "OLDPWD", old_path);
	uptade_env(&env, "PWD", new_path);
	free(old_path);
	free(new_path);
	return (0);
}

int	ft_cd_previous(t_env *env, char *old_path)
{
	uptade_env(&env, "PWD", search_value("OLDPWD", env));
	if (chdir(search_value("OLDPWD", env)) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (1);
	}
	ft_pwd();
	return (0);
}

int	ft_cd_home(t_env *env, char *old_path)
{
	uptade_env(&env, "PWD", search_value("HOME", env));
	if (chdir(search_value("HOME", env)) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_ast *ast, t_env *env)
{
	char	*old_path;
	char	*env_pwd;

	if (ast->token[1] && ast->token[2] != NULL)
	{
		write(2, "asauvage: cd: too many arguments\n", 34);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (!old_path)
	{
		env_pwd = search_value("PWD", env);
		if (env_pwd)
			old_path = ft_strdup(env_pwd);
		else
			return (1);
	}
	if (ast->token[1] == NULL)
	{
		ft_cd_home(env, old_path);
		return (0);
	}
	if (ft_strcmp(ast->token[1], "-") == 0)
		return (ft_cd_previous(env, old_path));
	return (ft_cd_basic(ast, env, old_path));
}
