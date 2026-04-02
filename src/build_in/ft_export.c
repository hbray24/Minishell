/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:28:16 by hbray             #+#    #+#             */
/*   Updated: 2026/04/02 15:47:20 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_in_alphabatical_order(t_env *env)
{
	t_env	*new_env;
	t_env	*env_cmp;
	char	*tmp;

	new_env = env;
	tmp = NULL;
	while (new_env)
	{
		env_cmp = new_env->next;
		while (env_cmp)
		{
			if (ft_strcmp(new_env->key, env_cmp->key) > 0)
			{
				tmp = new_env->key;
				new_env->key = env_cmp->key;
				env_cmp->key = tmp;
				tmp = new_env->value;
				new_env->value = env_cmp->value;
				env_cmp->value = tmp;
			}
			env_cmp = env_cmp->next;
		}
		new_env = new_env->next;
	}
	return (env);
}

void	ft_printf_export(t_env *env)
{
	t_env	*tmp;

	tmp = env_in_alphabatical_order(env);
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else
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
