/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brut_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:28:08 by hbray             #+#    #+#             */
/*   Updated: 2026/04/01 14:16:44 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_ast *ast, t_env *env)
{
	char	*old_path;
	char	*new_path;

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

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("hbray: ");
		return (0);
	}
	printf("%s\n", path);
	free(path);
	return (1);
}

void	ft_env(t_env **env)
{
	t_env	*current_env;

	current_env = *env;
	while (current_env)
	{
		printf("%s=", current_env->key);
		printf("%s\n", current_env->value);
		current_env = current_env->next;
	}
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != ' ')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
void	ft_export(t_ast *ast, t_env **env)
{
	char	*new_key;
	int		i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp((*env)->key, ast->token))
		{
			new_key = ft_strcpy(new_key, (*env)->key);
			break ;
		}
		*env = (*env)->next;
	}
	ast = ast->token[i++];
	while (ast->token)
	{
		if (!is_valid(ast->token))
		{
			write(2, "not a valid indentifier", 24);
			return ;
		}
		else
		{
			new_key = ft_strchr(ast->token, '=');
			while ((*env))
			{
				if (ft_strcmp(new_key, (*env)->key) == 0)
				{
					ft_strlcpy();
				}
				(*env) = (*env)->next;
			}
		}
		ast = ast->token[i++];
	}
	return ;
}
