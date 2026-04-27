/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:28:35 by hbray             #+#    #+#             */
/*   Updated: 2026/04/27 11:19:34 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*search_value(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*search_key(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->key);
		env = env->next;
	}
	return (NULL);
}

int	single_or_double_q(char **str)
{
	int	i;

	i = 0;
	while (str && *str && (*str)[i])
	{
		if ((*str)[i] == '\"')
			return (delete_quote(str));
		else if ((*str)[i] == '\'')
			return (delete_quote(str));
		i++;
	}
	return (1);
}

char	*alloc_new_str(int len)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		perror("Minishell :alloc_new_str");
	return (res);
}

char	*search_variable(char *str, t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(env->status);
			if (!tmp)
				return (NULL);
			str = realloc_token(str, i + 1, 1, tmp);
			free(tmp);
			if (!str)
				return (NULL);
			i += 2;
		}
		else if (str[i] == '$')
			str = expand_env_var(str, env, &i);
		else
			i++;
		if (!str)
			return (NULL);
	}
	return (str);
}
