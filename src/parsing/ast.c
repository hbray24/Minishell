/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:01:58 by asauvage          #+#    #+#             */
/*   Updated: 2026/04/23 11:16:49 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	copy_array(char **res, char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		res[i] = ft_strdup(cmd[i]);
		if (!res[i])
		{
			free_array(res);
			free_array(cmd);
			perror("Minishell :copy_array");
			return (-1);
		}
		i++;
	}
	free_array(cmd);
	return (i);
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
		perror("Minishell :add_array");
		return (NULL);
	}
	i = copy_array(res, cmd);
	if (i == -1)
		return (NULL);
	res[i] = ft_strdup(new_str);
	if (!res[i])
	{
		free_array(res);
		perror("Minishell :add_array");
		return (NULL);
	}
	res[++i] = NULL;
	return (res);
}

int	add_node_element(t_ast *ast, t_token *token, int *i)
{
	if (token->token == NULL)
		return (1);
	if (token->type == WORD)
	{
		ast->token = add_array(ast->token, token->token);
		if (!ast->token)
			return (0);
	}
	else if (token->type == REDIR_ADD || token->type == REDIR_IN
		|| token->type == REDIR_OUT || token->type == HERE_DOC)
		ast->redir[(*i)++] = token->type;
	else if (token->type == FILES)
	{
		ast->files = add_array(ast->files, token->token);
		if (!ast->files)
			return (0);
	}
	else if (token->type == LIMITER)
	{
		ast->limiter = add_array(ast->limiter, token->token);
		if (!ast->limiter)
			return (0);
	}
	return (1);
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
		perror("Minishell :fill_exec_node");
		return (NULL);
	}
	while (token && token->type != PIPE)
	{
		if (!add_node_element(ast, token, &i))
			return (NULL);
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
