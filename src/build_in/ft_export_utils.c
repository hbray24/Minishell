/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:35:32 by hbray             #+#    #+#             */
/*   Updated: 2026/04/03 15:44:41 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*swap_node(t_env *env, t_env *env_cmp)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_value = env_cmp->value;
	tmp_key = env_cmp->key;
	env_cmp->value = env->value;
	env_cmp->key = env->key;
	env->key = tmp_key;
	env->value = tmp_value;
	return (env);
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

char	*get_value(char *str)
{
	char	*res;

	res = ft_strchr(str, '=');
	if (!res)
		return (NULL);
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
