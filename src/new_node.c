/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:56:30 by hbray             #+#    #+#             */
/*   Updated: 2026/04/10 16:16:33 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new->fd[0] = -1;
	new->fd[1] = -1;
	return (new);
}
