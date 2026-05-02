/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:49:35 by hbray             #+#    #+#             */
/*   Updated: 2026/05/02 14:37:04 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*search_pipe(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens && !tokens->limite)
	{
		if (ft_strcmp(tokens->token, "|") == 0)
			return (tokens);
		tokens = tokens->pre;
	}
	return (NULL);
}

int	count_redir(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token && !token->limite)
	{
		if (token->type == REDIR_ADD || token->type == REDIR_IN
			|| token->type == REDIR_OUT)
			i++;
		token = token->next;
	}
	return (i);
}
