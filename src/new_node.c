/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:56:30 by hbray             #+#    #+#             */
/*   Updated: 2026/04/02 16:16:42 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	create_env(t_env *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		write(2, "asauvage: Malooc\n", 18);
		return (1);
	}
	ft_memset(new_env, 0, sizeof(t_env));
	env->next = new_env;
	new_env->next = NULL;
	new_env->pre = env;
	new_env->key = NULL;
	new_env->value = NULL;
	return (0);
} */

int	create_token(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		write(2, "Hbray: Malloc\n", 15);
		return (0);
	}
	ft_memset(new_token, 0, sizeof(t_token));
	token = last_token(&token);
	token->limite = 0;
	token->next = new_token;
	new_token->pre = token;
	new_token->token = NULL;
	new_token->next = NULL;
	return (1);
}

t_ast	*new_ast_node(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_ast));
	return (new);
}
