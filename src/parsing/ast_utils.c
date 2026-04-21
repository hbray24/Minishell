/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:49:35 by hbray             #+#    #+#             */
/*   Updated: 2026/04/21 11:38:34 by hbray            ###   ########.fr       */
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
			|| token->type == REDIR_OUT || token->type == HERE_DOC)
			i++;
		token = token->next;
	}
	return (i);
}
