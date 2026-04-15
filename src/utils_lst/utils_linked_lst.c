/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:56:30 by hbray             #+#    #+#             */
/*   Updated: 2026/04/15 18:22:27 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("Minishell");
		return (NULL);
	}
	ft_memset(new, 0, sizeof(t_ast));
	new->fd[0] = -2;
	new->fd[1] = -2;
	return (new);
}

int	add_node_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Minishell");
		return (1);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	new_node->pre = NULL;
	if (!*env)
	{
		*env = new_node;
		return (0);
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->pre = tmp;
	return (0);
}

t_env	*last_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
