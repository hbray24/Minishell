/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:28:35 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 11:38:25 by hbray            ###   ########.fr       */
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
		perror("Minishell");
	return (res);
}
