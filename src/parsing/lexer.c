/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:58:14 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/23 14:38:14 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	err_syntax(char *str)
{
	write(2, "syntax error near unexpected token '", 36);
	ft_putstr_fd(str, 2);
	write(2, "'\n", 2);
	return (2);
}

int	check_syntax(t_token *token)
{
	token = last_token(&token);
	if (!token)
		return (0);
	if (!token->pre && token->type == PIPE)
		return (err_syntax(token->token));
	if (token->pre && (token->pre->type > 3 && token->pre->type < 9)
		&& (token->type > 2 && token->type < 9))
		return (err_syntax(token->pre->token));
	return (0);
}

int	check_last_token(t_token *token)
{
	token = last_token(&token);
	if (!token)
		return (0);
	if (token->type > 2 && token->type < 9)
		return (err_syntax("newline"));
	return (0);
}

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
	status = check_syntax(token);
	return (status);
}

int	lexer(char *str, t_token *token, t_env **env)
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
			return ((*env)->status = status);
		}
		i++;
	}
	status = check_last_token(token);
	free_array(tokens);
	return (status);
}
