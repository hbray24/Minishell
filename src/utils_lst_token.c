/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:43:45 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/24 14:58:59 by asauvage         ###   ########.fr       */
/*   Updated: 2026/03/24 11:21:54 by hbray            ###   ########.fr       */
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

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
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
	token = last_token(token);
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
	token = last_token(token);
	token->token = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	return (0);
}
