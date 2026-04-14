/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:01:58 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/14 15:23:46 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**add_array(char **cmd, char *new_str)
{
	int		i;
	char	**res;

	i = 0;
	while (cmd && cmd[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
	{
		perror("Minishell");
		return (NULL);
	}
	i = 0;
	while (cmd && cmd[i])
	{
		res[i] = ft_strdup(cmd[i]);
		if (!res[i])
		{
			free_array(res);
			free_array(cmd);
			perror("Minishell");
			return (NULL);
		}
		i++;
	}
	free_array(cmd);
	res[i] = ft_strdup(new_str);
	if (!res[i])
	{
		free_array(res);
		perror("Minishell");
		return (NULL);
	}
	res[++i] = NULL;
	return (res);
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

t_ast	*fill_exec_node(t_ast *ast, t_token *token)
{
	int	i;

	i = 0;
	ast->token = NULL;
	ast->files = NULL;
	ast->type = EXEC;
	while (token->pre && !token->pre->limite && token->type != PIPE)
		token = token->pre;
	ast->redir = malloc(sizeof(t_type) * count_redir(token));
	if (!ast->redir)
	{
		perror("Minishell");
		return (NULL);
	}
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			ast->token = add_array(ast->token, token->token);
			if (!ast->token)
				return (NULL);
		}
		else if (token->type == REDIR_ADD || token->type == REDIR_IN
			|| token->type == REDIR_OUT || token->type == HERE_DOC)
			ast->redir[i++] = token->type;
		else if (token->type == FILES)
		{
			ast->files = add_array(ast->files, token->token);
			if (!ast->files)
				return (NULL);
		}
		else if (token->type == LIMITER)
		{
			ast->limiter = add_array(ast->limiter, token->token);
			if (!ast->limiter)
				return (NULL);
		}
		token = token->next;
	}
	return (ast);
}

t_ast	*parsing(t_token *token)
{
	t_ast	*ast;
	t_token	*tmp_token;

	tmp_token = search_pipe(token);
	ast = new_ast_node();
	if (!ast)
		return (NULL);
	if (tmp_token)
	{
		ast->type = PIPE;
		tmp_token->limite = 1;
		ast->r_child = parsing(tmp_token->next);
		if (!ast->r_child)
			return (NULL);
		ast->l_child = parsing(tmp_token->pre);
		if (!ast->l_child)
			return (NULL);
		return (ast);
	}
	if (token)
		ast = fill_exec_node(ast, token);
	return (ast);
}
