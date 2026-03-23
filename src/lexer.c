/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:58:14 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/23 20:33:14 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_token(char *str, t_token *token)
{
	int		status;

	status = 0;
	if (!ft_strcmp(str, "|"))
		status |= add_node(token, str, PIPE);
	else if (!ft_strcmp(str, "<"))
		status |= add_node(token, str, REDIR_IN);
	else if (!ft_strcmp(str, "<<"))
		status |= add_node(token, str, HERE_DOC);
	else if (!ft_strcmp(str, ">"))
		status |= add_node(token, str, REDIR_OUT);
	else if (!ft_strcmp(str, ">>"))
		status |= add_node(token, str, REDIR_ADD);
	else
		status |= add_node(token, str, WORD);
	if (status)
		clear_token(token);
	return (status);
}

void	print_token(t_token *token)
{
	token = first_token(token);
	while (token)
	{
		printf("%s, %d\n", token->token, token->type);
		token = token->next;
	}
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
		status |= fill_token(tokens[i], token);
		if (status)
		{
			free_array(tokens);
			return (status);
		}
		i++;
	}
	print_token(token);
	return (status);
}
