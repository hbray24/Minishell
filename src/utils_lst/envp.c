/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:25:58 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 16:36:28 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_env));
	node->key = key;
	node->value = value;
	return (node);
}

void	add_env(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->pre = tmp;
}

int	uptade_env(t_env **env, char *key, char *new_value)
{
	t_env	*new_env;

	new_env = *env;
	while (new_env)
	{
		if (ft_strcmp(new_env->key, key) == 0)
		{
			free(new_env->value);
			new_env->value = ft_strdup(new_value);
			if (!new_env->value)
			{
				perror("Minishell");
				return (0);
			}
			return (1);
		}
		new_env = new_env->next;
	}
	add_env(env, create_env_node(ft_strdup(key), ft_strdup(new_value)));
	return (1);
}

void	update_shlvl(t_env **env)
{
	t_env	*tmp;
	int		shlvl;
	char	*new_shlvl;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(tmp->value) + 1;
			new_shlvl = ft_itoa(shlvl);
			uptade_env(env, "SHLVL", new_shlvl);
			free(new_shlvl);
			return ;
		}
		tmp = tmp->next;
	}
}

void	without_env(t_env **env_list)
{
	char	*pwd;

	if (!search_value ("PWD", *env_list))
	{
		pwd = getcwd(NULL, 0);
		add_env(env_list, create_env_node(ft_strdup("PWD"), pwd));
	}
	if (!search_value("SHLVL", *env_list))
		add_env(env_list, create_env_node(ft_strdup("SHLVL"), ft_strdup("1")));
	else
		update_shlvl(env_list);
	if (!search_value("OLDPWD", *env_list))
		add_env(env_list, create_env_node(ft_strdup("OLDPWD"), NULL));
	if (!search_value("_", *env_list))
		add_env(env_list, create_env_node(ft_strdup("_"), ft_strdup("/usr/bin/env")));
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	int		i;
	int		j;
	char	*key;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
		if (envp[i][j] == '=')
			value = ft_strdup(envp[i] + j + 1);
		else
			value = NULL;
		add_env(&env_list, create_env_node(key, value));
		i++;
	}
	without_env(&env_list);
	return (env_list);
}
