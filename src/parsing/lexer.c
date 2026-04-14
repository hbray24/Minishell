/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:58:14 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/14 14:36:03 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_token(char *str, t_token *token)
{
	int		status;
	t_token	*tmp;

	tmp = last_token(&token);
	status = 0;
	if (!ft_strcmp(str, "|"))
		status = add_node(token, str, PIPE);
	else if (!ft_strcmp(str, "<"))
		status = add_node(token, str, REDIR_IN);
	else if (!ft_strcmp(str, "<<"))
		status = add_node(token, str, HERE_DOC);
	else if (!ft_strcmp(str, ">"))
		status = add_node(token, str, REDIR_OUT);
	else if (!ft_strcmp(str, ">>"))
		status = add_node(token, str, REDIR_ADD);
	else if (tmp && (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_ADD))
		status = add_node(token, str, FILES);
	else if (tmp && tmp->type == HERE_DOC)
		status = add_node(token, str, LIMITER);
	else
		status = add_node(token, str, WORD);
	return (status);
}

int	lexer(char *str, t_token *token)
{
	int		i;
	int		status;
	char	**tokens;

	tokens = split(str);
	if (!tokens)
	{
		write(2, "Hbray: Malloc\n", 15);
		return (1);
	}
	i = 0;
	status = 0;
	while (tokens[i])
	{
		status = fill_token(tokens[i], token);
		if (status)
		{
			free_array(tokens);
			return (status);
		}
		i++;
	}
	free_array(tokens);
	return (status);
}
