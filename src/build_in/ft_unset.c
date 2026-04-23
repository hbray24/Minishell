/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:02:31 by hbray             #+#    #+#             */
/*   Updated: 2026/04/23 16:40:31 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_node(t_env **env, t_env *tmp)
{
	t_env	*tmp2;

	free(tmp->key);
	free(tmp->value);
	if (tmp->pre)
		tmp->pre->next = tmp->next;
	else
		*env = tmp->next;
	if (tmp->next)
		tmp->next->pre = tmp->pre;
	tmp2 = tmp;
	free(tmp2);
}

void	ft_unset(t_ast *ast, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp_node_next;
	int		i;

	i = 0;
	if (!ast || !ast->token[1] || !env || !*env)
		return ;
	while (ast->token[++i])
	{
		tmp = *env;
		while (tmp)
		{
			tmp_node_next = tmp->next;
			if (!ft_strcmp(tmp->key, ast->token[i]))
				delete_node(env, tmp);
			tmp = tmp_node_next;
		}
	}
}
