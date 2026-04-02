/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:29:31 by hbray             #+#    #+#             */
/*   Updated: 2026/04/02 11:40:59 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd2(t_ast *ast, t_env *env, char *old_path)
{
	char	*new_path;

	if (chdir(ast->token[1]) == -1)
	{
		perror("hbray: cd");
		free(old_path);
		return (0);
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(old_path);
		return (0);
	}
	uptade_env(&env, "OLDPWD", old_path);
	uptade_env(&env, "PWD", new_path);
	free(old_path);
	free(new_path);
	return (1);
}

int	ft_cd(t_ast *ast, t_env *env)
{
	char	*old_path;

	if (ast->token[2] != NULL)
	{
		write(2, "asauvage: cd: too many arguments\n", 34);
		return (0);
	}
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (0);
	if (ft_strcmp(ast->token[1], "-") == 0)
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
	return (ft_cd2(ast, env, old_path));
}
