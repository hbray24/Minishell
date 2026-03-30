/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbray <hbray@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:01:58 by asauvage          #+#    #+#             */
/*   Updated: 2026/03/30 15:24:55 by hbray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = 0;
	new->token = NULL;
	new->l_child = NULL;
	new->r_child = NULL;
	return (new);
}

t_token	*search_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->token, "|") == 0)
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
		if (ft_strcmp(token->token, "<<") == 0 || ft_strcmp(token->token,
				">>") == 0 || ft_strcmp(token->token, "<") == 0
			|| ft_strcmp(token->token, ">") == 0)
			return (token);
		token = token->pre;
	}
	return (NULL);
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
	if (!res)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		res[i] = ft_strdup(cmd[i]);
		i++;
	}
	res[i++] = ft_strdup(new_str);
	res[i] = NULL;
	free_array(cmd);
	return (res);
}
int	count_redir(t_token *token)
{
	int	i;

	i = 0;
	while (token)
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
	while (token && token->pre && token->type != PIPE)
		token = token->pre;
	ast->redir = malloc(sizeof(t_type) * count_redir(token));
	if (!ast->redir)
		return(NULL);
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			ast->token = add_array(ast->token, token->token);
		else if (token->type == REDIR_ADD || token->type == REDIR_IN
			|| token->type == REDIR_OUT || token->type == HERE_DOC)
			ast->redir[i++] = token->type;
		else if (token->type == FILES)
			ast->files = add_array(ast->files, token->token);
		else if (token->type == LIMITER)
			ast->limiter = add_array(ast->limiter, token->token);
		token = token->next;
	}
	return (ast);
}

t_ast	*parsing(t_token *token)
{
	t_ast	*ast;
	t_token	*token_right;
	t_token	*token_left;
	t_token	*tmp_token;

	tmp_token = search_pipe(token);
	ast = new_ast_node();
	if (tmp_token)
	{
		ast->type = PIPE;
		token_left = token->pre;
		token_right = token->next;
		if (token_right)
			token_right->pre = NULL;
		if (token_left)
			token_left->next = NULL;
		ast->l_child = parsing(token_left);
		ast->r_child = parsing(token_right);
		return (ast);
	}
	ast = fill_exec_node(ast, token);
	return (ast);
}
