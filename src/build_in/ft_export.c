/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:28:16 by hbray             #+#    #+#             */
/*   Updated: 2026/04/02 18:56:27 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env(t_env	*env)
{
	t_env	*cpy_env;

	cpy_env = NULL;
	while (env)
	{
		add_node_env(&cpy_env, ft_strdup(env->key), ft_strdup(env->value));
		env = env->next;
	}
	return (cpy_env);
}

t_env	*env_in_alphabatical_order(t_env *env)
{
	t_env	*cpy_env;
	t_env	*env_cmp;
	t_env	*start;
	char	*tmp_key;
	char	*tmp_value;

	cpy_env = copy_env(env);
	start = cpy_env;
	while (cpy_env && cpy_env->next)
	{
		env_cmp = cpy_env->next;
		while (env_cmp)
		{
			if (ft_strcmp(cpy_env->key, env_cmp->key) > 0)
			{
				tmp_value = env_cmp->value;
				tmp_key = env_cmp->key;
				env_cmp->value = cpy_env->value;
				env_cmp->key = cpy_env->key;
				cpy_env->key = tmp_key;
				cpy_env->value = tmp_value;
			}
			env_cmp = env_cmp->next;
		}
		cpy_env = cpy_env->next;
	}
	return (start);
}

void	ft_printf_export(t_env *env)
{
	t_env	*tmp;

	tmp = env_in_alphabatical_order(env);
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key)
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	ft_export2(t_ast *ast, t_env **env, t_env *tmp, int i)
{
	char	*key;
	char	*value;

	key = get_key(ast->token[i]);
	value = get_value(ast->token[i]);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->value);
		tmp->value = value;
		free(key);
	}
	else
		add_node_env(env, key, value);
}

void	ft_export(t_ast *ast, t_env **env)
{
	t_env	*tmp;
	int		i;

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
		tmp = *env;
		ft_export2(ast, env, tmp, i);
		i++;
	}
}
