/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:29:31 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 11:35:37 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	if (ast->token[1][0] == '\0')
	{
		free(old_path);
		return (0);
	}
	if (ast->token[1][0] == '~')
	{
		if (!join_to_home(ast, env))
			return (1);
	}
	if (chdir(ast->token[1]) == -1)
	{
		perror("Minishell: cd");
		free(old_path);
		return (1);
	}
	new_path = search_new_path(ast, old_path);
	uptade_env(&env, "OLDPWD", old_path);
	uptade_env(&env, "PWD", new_path);
	free(old_path);
	free(new_path);
	return (0);
}

int	ft_cd_previous(t_env *env, char *old_path)
{
	if (!uptade_env(&env, "PWD", search_value("OLDPWD", env)))
		return (1);
	if (chdir(search_value("OLDPWD", env)) == -1)
	{
		perror("Minishell: cd");
		free(old_path);
		return (1);
	}
	return (ft_pwd());
}

int	ft_cd_home(t_env *env, char *old_path)
{
	if (!uptade_env(&env, "PWD", search_value("HOME", env)))
		return (1);
	if (chdir(search_value("HOME", env)) == -1)
	{
		perror("Minishell");
		free(old_path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_ast *ast, t_env *env)
{
	char	*old_path;

	if (ast->token[1] && ast->token[2] != NULL)
	{
		write(2, "Minishell: cd: too many arguments\n", 34);
		return (1);
	}
	old_path = search_old_path(env);
	if (!old_path)
		return (1);
	if (ast->token[1] == NULL)
		return (ft_cd_home(env, old_path));
	if (ft_strcmp(ast->token[1], "-") == 0)
		return (ft_cd_previous(env, old_path));
	return (ft_cd_basic(ast, env, old_path));
}
