/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:43:45 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/01 16:42:45 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*first_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->pre)
		token = token->pre;
	return (token);
}

t_token	*last_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (!token)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	create_token(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		write(2, "Hbray: Malloc\n", 15);
		return (0);
	}
	token = last_token(&token);
	token->limite = 0;
	token->next = new_token;
	new_token->pre = token;
	new_token->token = NULL;
	new_token->next = NULL;
	return (1);
}

int	add_node(t_token *token, char *str, int type)
{
	if (token->token)
	{
		if (!create_token(token))
			return (1);
	}
	token = last_token(&token);
	token->token = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	return (0);
}
t_env	*last_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if(!env)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	create_env(t_env *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		write(2, "asauvage: Malooc\n", 18);
		return (1);
	}
	env->next = new_env;
	new_env->next = env;
	new_env->key = NULL;
	new_env->value = NULL;
	return (0);
}

int	add_node_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return(1);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return(0);
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	return (0);
}
t_ast	*new_ast_node(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_ast));
	return (new);
}
