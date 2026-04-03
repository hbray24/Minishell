/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:02:31 by hbray             #+#    #+#             */
/*   Updated: 2026/04/03 10:14:49 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_ast *ast, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 0;
	if (!ast || !ast->token[1] || !env || !*env)
		return ;
	while (ast->token[++i])
	{
		tmp = *env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, ast->token[i]))
			{
				free(tmp->key);
				free(tmp->value);
				if (tmp->pre)
					tmp->pre->next = tmp->next;
				else
					*env = tmp->next;
				if (tmp->next)
					tmp->next->pre = tmp->pre;
				tmp2 = tmp;
				tmp = tmp->next;
				free(tmp2);
			}
			else
				tmp = tmp->next;
		}
	}
}
