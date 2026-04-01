/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brut_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:28:08 by hbray             #+#    #+#             */
/*   Updated: 2026/04/01 16:51:48 by hbray            ###   ########.fr       */
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
		if ( current_env->value != NULL)
			printf("%s=%s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
void	ft_printf_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
}

char	*get_value(char *str)
{
	char	*res;

	res = ft_strchr(str, '=');
	if (!res)
		return(NULL);
	return (ft_strdup(res + 1));
}

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

void	ft_export(t_ast *ast, t_env **env)
{
	int		i;
	t_env	*tmp;
	char	*key;
	char	*value;

	i = 1;
	if (!ast->token[1])
	{
		ft_printf_export(*env);
		return ;
	}
	while (ast->token[i])
	{
		if (!is_valid(ast->token[i]))
		{
			write(2, "export: not a valid indentifier\n", 33);
			i++;
			continue ;
		}
		key = get_key(ast->token[i]);
		value = get_value(ast->token[i]);
		tmp = *env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key,key))
				break ;
			tmp = tmp->next;
		}
		if (tmp)
		{
			if ( ft_strchr(ast->token[i], '='))
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = value;
			}
			else if (value)
				free(value);
			free(key);
		}
		else
			add_node_env(env, key, value);
		i++;
	}
}
