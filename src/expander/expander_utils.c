/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:28:35 by hbray             #+#    #+#             */
/*   Updated: 2026/04/28 14:54:56 by asauvage         ###   ########.fr       */
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
		if ((*str)[i] == '\"' || (*str)[i] == '\'')
			return (delete_quote(str));
		// else if ((*str)[i] == '\'')
		// 	return (delete_quote(str));
		i++;
	}
	return (1);
}

char	*alloc_new_str(int len)
{
	char	*res;

	printf("oui%d\n", len);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (perror("Minishell :alloc_new_str"), NULL);
	return (res);
}

char	*search_variable(char *str, t_env *env)
{
	char	*tmp;
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	tmp = NULL;
	while (str && str[i])
	{
		if (str[i] == '\'')
			flags = 1;
		if (flags != 1 && str[i] == '$' && str[i + 1] == '?')
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
		else if (flags != 1 && str[i] == '$')
			str = expand_env_var(str, env, &i);
		else
			i++;
		if (!str)
			return (NULL);

		if (str[i] == '\'' && flags == 1)
			flags = 0;
	}
	return (str);
}
