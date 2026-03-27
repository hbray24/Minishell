/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:01:58 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/27 15:35:41 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = type;
	new->token = NULL;
	new->l_child = NULL;
	new->r_child = NULL;
	return (new);
}

t_token	*search_pipe(t_token *tokens)
{
	tokens = last_token(&tokens);
	while (tokens)
	{
		if (ft_strcmp(tokens->token, '|') == 0)
			return (tokens);
		tokens = tokens->pre;
	}
	return (NULL);
}

t_token	*search_redir(t_token *token)
{
	token = last_token(&token);
	while (token)
	{
		if (ft_strcmp(token->token, '<<') == 0 || ft_strcmp(token->token, '>>') == 0
			|| ft_strcmp(token->token, '<') == 0 || ft_strcmp(token->token, '>') == 0)
			return (token);
		token = token->pre;
	}
	return (NULL);
}

t_ast	*check_redir(char *token)
{
	if (ft_strcmp(token, '<') == 0)
		return (new_ast_node(REDIR_IN));
	if (ft_strcmp(token, '>') == 0)
		return (new_ast_node(REDIR_OUT));
	if (ft_strcmp(token, '<<') == 0)
		return (new_ast_node(HERE_DOC));
	if (ft_strcmp(token, '>>') == 0)
		return (new_ast_node(REDIR_ADD));
}

char	**sub_strstr(char **str, int start, int end)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (end - start + 2));
	if (!res)
		return (NULL);
	while (start <= end)
		res[i++] = ft_strdup(str[start++]);
	res[i] = NULL;
	return (res);
}

char	**add_array(char **cmd, char *new_str)
{
	int		i;
	char	**res;

	i = 0;
	while (cmd && cmd[i])
		i++;
	res = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (cmd[i])
	{
		res[i] = ft_strdup(cmd[i]);
		i++;
	}
	res[i++] = ft_strdup(new_str);
	res[i] = NULL;
	free_array(cmd);
	return (res);
}

t_ast	*fill_exec_node(t_ast *ast, t_token *token)
{
	char	**cmd;
	char	**fd;
	char	**file;

	while (token->pre && token->type != PIPE)
		token = token->pre;
	while (token->next && token->type != PIPE)
	{
		if (token->type == WORD)
			cmd = add_array(cmd, token->token);
		else if (token->type == REDIR_ADD || token->type == REDIR_IN || token->type == REDIR_OUT)
			 
	}
}

t_ast	*parsing(t_token *token)
{
	t_ast	*ast;
	t_token	*tmp_token;

	tmp_token = search_pipe(token);
	if (tmp_token)
	{
		ast = new_ast_node(PIPE);
		ast->l_child = parsing(token->pre);
		ast->r_child = parsing(token->next);
		return (ast);
	}
	tmp_token = search_redir(token);
	if (tmp_token)
	{
		ast = check_redir(token);
		ast = fill_exec_node(ast, token);
	}
	return(ast);
}
