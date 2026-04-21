/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:28:16 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 14:08:06 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*copy_env(t_env *env)
{
	t_env	*cpy_env;
	char	*cpy_value;

	cpy_env = NULL;
	cpy_value = NULL;
	while (env)
	{
		if (env->value)
			cpy_value = ft_strdup(env->value);
		else
			cpy_value = NULL;
		add_node_env(&cpy_env, ft_strdup(env->key), cpy_value);
		env = env->next;
	}
	return (cpy_env);
}

t_env	*env_in_alphabatical_order(t_env *env)
{
	t_env	*cpy_env;
	t_env	*env_cmp;
	t_env	*start;

	cpy_env = copy_env(env);
	start = cpy_env;
	while (cpy_env && cpy_env->next)
	{
		env_cmp = cpy_env->next;
		while (env_cmp)
		{
			if (ft_strcmp(cpy_env->key, env_cmp->key) > 0)
				cpy_env = swap_node(cpy_env, env_cmp);
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
	clear_env(&tmp);
}

void	modif_variable(t_ast *ast, t_env **env, t_env *tmp, int i)
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
		if (value)
		{
			free(tmp->value);
			tmp->value = value;
		}
		free(key);
	}
	else
		add_node_env(env, key, value);
}

int	ft_export(t_ast *ast, t_env **env)
{
	t_env	*tmp;
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (!ast->token[1])
	{
		ft_printf_export(*env);
		return (0);
	}
	while (ast->token[++i])
	{
		if (!is_valid(ast->token[i]))
		{
			write(2, "Minishell: export: '", 20);
			write(2, ast->token[i], ft_strlen(ast->token[i]));
			write(2, "': not a valid indentifier\n", 27);
			status = 1;
			continue ;
		}
		tmp = *env;
		modif_variable(ast, env, tmp, i);
	}
	return (status);
}
