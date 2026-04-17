/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:28:35 by hbray             #+#    #+#             */
/*   Updated: 2026/04/17 16:43:54 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return(env->key);
		env = env->next;
	}
	return(NULL);
}
