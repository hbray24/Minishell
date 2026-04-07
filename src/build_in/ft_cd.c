/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:29:31 by hbray             #+#    #+#             */
/*   Updated: 2026/04/07 15:53:42 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd2(t_ast *ast, t_env *env, char *old_path)
{
	char	*new_path;
	char	*tmp_path;

	if (chdir(ast->token[1]) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (0);
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
	return (1);
}

int	ft_cd_previous(t_env *env, char *old_path)
{
	uptade_env(&env, "PWD", search_value("OLDPWD", env));
	if (chdir(search_value("OLDPWD", env)) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (0);
	}
	ft_pwd();
	return (1);
}

int	ft_cd(t_ast *ast, t_env *env)
{
	char	*old_path;
	char	*env_pwd;

	if (ast->token[1] && ast->token[2] != NULL)
	{
		write(2, "asauvage: cd: too many arguments\n", 34);
		return (0);
	}
	old_path = getcwd(NULL, 0);
	if (!old_path)
	{
		env_pwd = search_value("PWD", env);
		if (env_pwd)
			old_path = ft_strdup(env_pwd);
		else
			return (0);
	}
	if (ast->token[1] == NULL)
	{
		uptade_env(&env, "PWD", search_value("HOME", env));
		if(chdir(search_value("HOME", env)) == -1)
		{
			perror("hbray: cd");
			free(old_path);
			return (0);
		}
		return(1);
	}
	if (ft_strcmp(ast->token[1], "-") == 0)
		return (ft_cd_previous(env, old_path));
	return (ft_cd2(ast, env, old_path));
}
