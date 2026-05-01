/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:43:45 by asauvage          #+#    #+#             */
/*   Updated: 2026/05/01 10:37:11 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*malloc_struct(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		write(2, "Minishell: Malloc\n", 19);
		return (NULL);
	}
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}

int	create_token(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		write(2, "Minishell: Malloc\n", 19);
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
